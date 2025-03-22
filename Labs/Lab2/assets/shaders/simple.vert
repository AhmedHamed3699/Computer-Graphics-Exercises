#version 330 core
void main() {
    // Create a constant array of data and fill it with data.
    const vec3 positions[3] = vec3[3](
        vec3( 0.5, -0.5, 0.0),
        vec3(-0.5, -0.5, 0.0),
        vec3( 0.0,  0.5, 0.0)
    );
    // Use the vertexID 
    gl_Position = vec4(positions[gl_VertexID], 1.0);
}
