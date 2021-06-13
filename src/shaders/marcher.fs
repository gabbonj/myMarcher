#version 420

#define MAX_LIGHTS 10

out vec4 FragColor;
in vec2 uv;

struct Light {
    vec3 position;
    vec3 color;
    float brightness;
};


uniform int light_number;
layout (binding = 1) uniform lights {
    Light scene_lights[MAX_LIGHTS];
};
uniform mat4 view_invers;
uniform mat4 camera_invers;
uniform int max_steps;
uniform float epsilon;
uniform float far_distance;
uniform float shadow_intensity;
uniform float shadow_bias;

int max_iter = 512;
int steps = 0;

mat2 rot(float alpha)
{
    float s = sin(alpha);
    float c = cos(alpha);
    return mat2(c, -s, s, c);
}

float distance_from_sphere(in vec3 position, in vec3 centre, float radius)
{
    // position.xz = mod(position.xz, 2.0);
	return length(position - centre) - radius;
}

float DE(vec3 pos) {
	float Bailout = 2.0;
    float Power = 8.0;
    vec3 z = pos;
	float dr = 1.0;
	float r = 0.0;
	for (int i = 0; i < max_iter ; i++) {
		r = length(z);
		if (r>Bailout) break;
		
		// convert to polar coordinates
		float theta = acos(z.z/r);
		float phi = atan(z.y,z.x);
		dr =  pow( r, Power-1.0)*Power*dr + 1.0;
		
		// scale and rotate the point
		float zr = pow( r,Power);
		theta = theta*Power;
		phi = phi*Power;
		
		// convert back to cartesian coordinates
		z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
		z+=pos;
	}
	return 0.5*log(r)*r/dr;
}

float map_the_world(vec3 position){
    float fractal = DE(position);
    // float sphere = distance_from_sphere(position, vec3(0.0), 0.5);
    return fractal;
}

vec3 calculteNormal(in vec3 p)
{
    const vec3 small_step = vec3(0.00001, 0.0, 0.0);

    float gradient_x = map_the_world(p + small_step.xyy) - map_the_world(p - small_step.xyy);
    float gradient_y = map_the_world(p + small_step.yxy) - map_the_world(p - small_step.yxy);
    float gradient_z = map_the_world(p + small_step.yyx) - map_the_world(p - small_step.yyx);

    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

    return normalize(normal);
}

float rayMarch(vec3 origin, vec3 direction)
{
    float ray_travel = 0.0;
    
    for (int i = 0; i < max_steps; ++i) {
        vec3 position = origin + ray_travel * direction;
        float scene_distance = map_the_world(position);
        ray_travel += scene_distance;
        if (ray_travel > far_distance || scene_distance < epsilon) {
            steps = i;
            break;
        };
    }
    return ray_travel;
}

vec3 getLight(vec3 position, Light light)
{ 
    vec3 light_direction = normalize(light.position - position);
    vec3 normal = calculteNormal(position);
    
    vec3 difuse = vec3(clamp(dot(normal, light_direction), 0.0, 1.0));
    float d  = rayMarch(position + normal * shadow_bias, light_direction);
    if (d < length(light.position - position)) { 
        difuse *= 1.0 - shadow_intensity;
    }else{
        difuse *= light.color * light.brightness;
    }

    return difuse;
}

void main()
{
    vec4 camera_position = view_invers  * vec4(0.0, 0.0, 0.0, 1.0);
    vec4 ray_direction = camera_invers * vec4(uv, 0.0, 1.0);
    ray_direction = view_invers * vec4(ray_direction.xyz, 0.0);
    ray_direction.xyz = normalize(ray_direction.xyz);

    float d = rayMarch(camera_position.xyz, ray_direction.xyz);
    if (d < far_distance) {
        vec3 current_position = camera_position.xyz + d * ray_direction.xyz;
        float occ = 1.0 - float(steps) / float(max_steps);
        
        vec3 difuse = vec3(0.0);
        for (int i = 0; i < light_number; i++) {
            difuse += getLight(current_position, scene_lights[i]);
        }
        vec3 col = vec3(difuse * occ);
        FragColor = vec4(col, 1.0);
    }else{
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
} 