当你想要实现广告牌效果而不改变模型矩阵时，通常使用几何着色器（Geometry Shader）或在片段着色器中进行计算来实现这一目标。这样，你可以在渲染阶段通过改变顶点的位置或方向来使广告牌始终朝向摄像机。

下面是一个使用片段着色器的简单示例，展示了如何实现广告牌效果，而不改变模型矩阵：

// 片段着色器代码
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform mat4 view;
    void main()
    {
        vec3 cameraRight = vec3(view[0][0], view[1][0], view[2][0]);
        vec3 cameraUp = vec3(view[0][1], view[1][1], view[2][1]);

        vec3 viewDir = normalize(-vec3(view[0][2], view[1][2], view[2][2]));
        vec3 billboardNormal = cross(cameraRight, cameraUp);

        vec3 rotatedPosition = billboardNormal * gl_PointCoord.x +
                               cross(billboardNormal, viewDir) * gl_PointCoord.y +
                               viewDir;

        FragColor = vec4(rotatedPosition, 1.0);
    }
)";


在这个示例中，片段着色器计算出在广告牌上的每个片段的位置，以使其始终面向摄像机。这种方法将片段着色器中的点的位置从2D纹理坐标转换到3D空间中，从而实现了广告牌效果。请注意，这只是一个简单的示例，实际使用时你可能需要根据场景的需求进行适当的调整和优化。

这种方法通常适用于粒子系统、树叶、火焰等效果，它可以在不更改模型矩阵的情况下实现面向摄像机的效果。

使用法线来实现广告牌效果是一种常见的方法，但要注意的是，这种方法适用于特定类型的广告牌，例如平面的广告牌（例如树叶）。对于具有复杂形状的物体，使用法线可能会导致不符合预期的效果。

基本思路是使用物体的法线向量来确定物体的朝向，然后将顶点位置沿着该法线进行适当的调整，从而使物体始终朝向摄像机。

以下是一个简单的示例片段着色器，演示了如何使用物体的法线来实现广告牌效果：

// 片段着色器代码
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 FragNormal;
    uniform mat4 view;
    void main()
    {
        vec3 cameraDir = normalize(vec3(view[3][0], view[3][1], view[3][2]));

        vec3 rotatedNormal = normalize(cross(FragNormal, cameraDir));
        FragColor = vec4(rotatedNormal, 1.0);
    }
)";
在这个示例中，我们假设顶点着色器已经计算并传递了每个顶点的法线向量（FragNormal）。然后，我们使用顶点着色器计算得到的法线向量和摄像机方向之间的叉积，得到一个新的法线向量，该向量用于计算每个片段的颜色。这样，每个片段都会根据物体的法线朝向适当的方向。

需要注意的是，这种方法的适用范围有限，因为它假设物体本身是平面的，而且不适合具有复杂几何形状的物体。对于更复杂的物体，可能需要使用更复杂的技术，如在片段着色器中使用几何着色器或计算来实现面向摄像机的效果。