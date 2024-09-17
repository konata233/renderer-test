#include <iostream>
#include "dependencies/Vector.h"
#include "dependencies/Matrix.h"
#include "dependencies/Transform.h"
#include "dependencies/Renderer.h"
#include "dependencies/Mesh.h"
#include "dependencies/Vertex.h"
#include "dependencies/Device.h"

int main() {
    std::cout << "----------start rendering-------------" << std::endl;
    bool err = false;
    Renderer renderer = Renderer(100, 100, 4);
    ImageOutputDevice device = ImageOutputDevice();
    device.bind_source(renderer.get_screen_buffer());

    Vertex<float> vt0 = Vertex<float>(vec4f(-0.5, -0.5, 0, 1));
    VertexShader<float> vs0 = VertexShader<float>(&vt0, [](VertexShaderContext<float>& ctx){return Color(255, 0, 0);});
    vt0.set_shader(vs0);

    Vertex<float> vt1 = Vertex<float>(vec4f(0.5, -0.5, 0, 1));
    VertexShader<float> vs1 = VertexShader<float>(&vt1, [](VertexShaderContext<float>& ctx){return Color(0, 255, 0);});
    vt1.set_shader(vs1);

    Vertex<float> vt2 = Vertex<float>(vec4f(0.0, 0.5, 0, 1));
    VertexShader<float> vs2 = VertexShader<float>(&vt2, [](VertexShaderContext<float>& ctx){return Color(0, 0, 255);});
    vt2.set_shader(vs2);

    Vertex<float> vertices[3] = {vt0, vt1, vt2};
    Triangle<float> triangle = Triangle<float>(vertices);

    FragmentShader<float> fs = FragmentShader<float>([](FragmentShaderContext<float>& ctx) {return ctx.color_interpolated;});
    Mesh<float> mesh = Mesh(fs);

    Vertex<float> vt3 = Vertex<float>(vec4f(-0.5, -0.5, 0, 1));
    VertexShader<float> vs3 = VertexShader<float>(&vt3, [](VertexShaderContext<float>& ctx){return Color(255, 255, 0);});
    vt3.set_shader(vs3);

    Vertex<float> vt4 = Vertex<float>(vec4f(0.5, -0.5, 0, 1));
    VertexShader<float> vs4 = VertexShader<float>(&vt4, [](VertexShaderContext<float>& ctx){return Color(0, 255, 255);});
    vt4.set_shader(vs4);

    Vertex<float> vt5 = Vertex<float>(vec4f(0.0, 0.5, 0, 1));
    VertexShader<float> vs5 = VertexShader<float>(&vt5, [](VertexShaderContext<float>& ctx){return Color(255, 0, 255);});
    vt5.set_shader(vs5);

    Vertex<float> vertices2[3] = {vt3, vt4, vt5};
    Triangle<float> triangle2 = Triangle<float>(vertices2);

    FragmentShader<float> fs2 = FragmentShader<float>([](FragmentShaderContext<float>& ctx) {return ctx.color_interpolated;});
    Mesh<float> mesh2 = Mesh(fs2);

    auto v = trans_f::view(vec3f(0, 0, 0), vec3f(0, 0, 1), vec3f(0, 1, 0), err);
    auto f = Transform<float>::frustum(RAD(60), 1, 100, 0.0001);
    auto o = trans_f::orthographic(-1, 1, -1, 1, 1, 0.0001);
    auto vp = Transform<float>::viewport(100, 100, 4);

    auto pt = f * v;
    auto model = trans_f::translate(-0.1, 0, 1) * trans_f::rotate(RAD(45), RAD(0), RAD(30));
    std::cout << (v * model).pretty_print();
    mesh.append_triangle(triangle)->apply_model_transform(model)->apply_view_persp_transform(pt)->apply_viewport_transform(vp)->ready();

    auto model2 = trans_f::translate(-0.1, 0, 1) * trans_f::rotate(RAD(-45), RAD(20), RAD(0));
    mesh2.append_triangle(triangle2)->apply_model_transform(model2)->apply_view_persp_transform(pt)->apply_viewport_transform(vp)->ready();

    renderer.append_mesh(mesh)->append_mesh(mesh2);
    renderer.render_all();
    device.write_to_file("test.png");
}
