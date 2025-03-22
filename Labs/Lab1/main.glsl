void main() {
    if (gl_FragCoord.x < iResolution.x * 0.5 + sin(gl_FragCoord.y * 0.1 + iTime * 10.0) * 20.0)
        gl_FragColor = vec4(gl_FragCoord.xy/iResolution.xy, 0, 1);
    else
        gl_FragColor = vec4(0, gl_FragCoord.xy/iResolution.xy, 1);

    vec2 leftCircleCenter  = vec2(iResolution.x * 0.25, iResolution.y * 0.5);
    vec2 rightCircleCenter = vec2(iResolution.x * 0.75, iResolution.y * 0.5);
    if (distance(gl_FragCoord.xy, leftCircleCenter) < 50.0)
        gl_FragColor = vec4(0.5 * sin(iTime) + 0.5, 0.5 * sin(iTime + 1.0) + 0.5, 0.5 * sin(iTime + 2.0), 1);
    if (distance(gl_FragCoord.xy, rightCircleCenter) < 50.0)
        gl_FragColor = vec4(0.5 * sin(iTime) + 0.5, 0.5 * sin(iTime + 2.0), 0.5 * sin(iTime + 1.0), 1);
}