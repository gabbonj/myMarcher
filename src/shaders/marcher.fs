#version 330 core

out vec4 FragColor;
in vec2 uv;

uniform mat4 view_invers;
uniform mat4 camera_invers;

int iter = 0;
int max_iter = 100;

mat2 rot(float alpha)
{
    float s = sin(alpha);
    float c = cos(alpha);
    return mat2(c, -s, s, c);
}

float distance_from_sphere(in vec3 position, in vec3 centre, float radius)
{
    position.xz = mod(position.xz, 2.0);
	return length(position - centre) - radius;
}

float DE(vec3 pos) {
	float Bailout = 2.0;
    float Power = 6.0;
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
        iter++;
	}
	return 0.5*log(r)*r/dr;
}

float map_the_world(vec3 position){
    return DE(position);
}

vec3 calculate_normal(in vec3 p)
{
    const vec3 small_step = vec3(0.00001, 0.0, 0.0);

    float gradient_x = map_the_world(p + small_step.xyy) - map_the_world(p - small_step.xyy);
    float gradient_y = map_the_world(p + small_step.yxy) - map_the_world(p - small_step.yxy);
    float gradient_z = map_the_world(p + small_step.yyx) - map_the_world(p - small_step.yyx);

    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

    return normalize(normal);
}

vec3 rayMarch(in vec3 ro, in vec3 rd)
{
    float total_distance_traveled = 0.0;
    const int NUMBER_OF_STEPS = 128;
    const float MINIMUM_HIT_DISTANCE = 0.0005;
    const float MAXIMUM_TRACE_DISTANCE = 10.0;

    for (int i = 0; i < NUMBER_OF_STEPS; ++i)
    {
        vec3 current_position = ro + total_distance_traveled * rd;

        float distance_to_closest = map_the_world(current_position);

        if (distance_to_closest < MINIMUM_HIT_DISTANCE) 
        {
            vec3 normal = calculate_normal(current_position);
            vec3 light_position = vec3(2.0, -3.0, 3.0);

            vec3 direction_to_light = normalize(current_position - light_position);

            float diffuse_intensity = max(0.0, dot(normal, direction_to_light));
            float occ = 1 - float(i) / float(NUMBER_OF_STEPS);
            float iter_clamp = float(iter) / float(max_iter);

            return vec3(iter_clamp, 1.0, 1.0 - iter_clamp) * diffuse_intensity  * occ;
        }

        if (total_distance_traveled > MAXIMUM_TRACE_DISTANCE)
        {
            break;
        }
        total_distance_traveled += distance_to_closest;
    }
    return vec3(0.0);
}

void main()
{
    vec4 camera_position = view_invers  * vec4(0.0, 0.0, 0.0, 1.0);
    vec4 ray_direction = camera_invers * vec4(uv, 0.0, 1.0);
    ray_direction = view_invers * vec4(ray_direction.xyz, 0.0);

    vec3 color = rayMarch(camera_position.xyz, normalize(ray_direction.xyz));
    FragColor = vec4(color, .0f);
} 