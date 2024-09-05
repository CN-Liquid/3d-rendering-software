#include<iostream>
#include<SDL2/SDL.h>
#include<cmath>
#include"headers/triangle.h"
#include<fstream>
#include<sstream>
#include<vector>
#include<array>
#define SCENE_LENGTH 1000
#define SCENE_WIDTH 700


class scene 
{
    float cx=0,cy=0,cz=0;
    triangle *t;
    std::vector<std::array<float,4>> vertices;
    std::vector<std::array<int,3>> indices;
    std::vector<triangle> trianglestodraw;

    int indices_num=0;
      public:
   
  
    bool load_object_from_file(const std::string& file)
{
    std::ifstream f(file);
    if (!f.is_open())
    {
        std::cerr << "Failed to open file: " << file << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(f, line))
    {
        std::stringstream stmt(line);
        char type;
        if (line[0] == 'v')
        {
            std::array<float, 4> m = {0.0f, 0.0f, 0.0f, 1.0f};
            stmt >> type >> m[0] >> m[1] >> m[2]; 
            m[2]=m[2]+50;
            vertices.push_back(m);
        }
        else if (line[0] == 'f')
        {
            std::array<int, 3> m = {0, 0, 0};
            stmt >> type >> m[0] >> m[1] >> m[2];
            indices.push_back(m);
            indices_num++;
        }
    }
    return true;
}
    void populate()
    {
        for(int i=0;i<indices_num;i++)
        {
            float vertex1[]={vertices[indices[i][0]-1][0],vertices[indices[i][0]-1][1],vertices[indices[i][0]-1][2]};
            float vertex2[]={vertices[indices[i][1]-1][0],vertices[indices[i][1]-1][1],vertices[indices[i][1]-1][2]};
            float vertex3[]={vertices[indices[i][2]-1][0],vertices[indices[i][2]-1][1],vertices[indices[i][2]-1][2]};
            triangle t;

        t.get_data(vertex1,vertex2,vertex3,255,255,255);

        trianglestodraw.push_back(t);
        }
        //delete[] t;
        //t=nullptr;
    }

    void render_scene(SDL_Renderer * renderer)
    {
        sort(trianglestodraw.begin(),trianglestodraw.end(),[](triangle &t1,triangle &t2)
            {
                float z1=(t1.p1.p[2]+t1.p2.p[2]+t1.p3.p[2])/3.0f;
                float z2=(t2.p1.p[2]+t2.p2.p[2]+t2.p3.p[2])/3.0f;
                return z1>z2;
            });
        for(int i=0;i<trianglestodraw.size();i++)
        {
            trianglestodraw[i].draw_triangle(renderer);
        }
        
    }
    void scene_translate_z(float dz,int n) 
        {
        for(int i = 0; i < trianglestodraw.size(); ++i) 
        {
            trianglestodraw[i].translate_z(dz,n);
        }
        cz=cz-n*dz;
        }
        void scene_translate_x(float dz,int n) 
        {
        for(int i = 0; i < trianglestodraw.size(); ++i) 
        {
            trianglestodraw[i].translate_x(dz,n);
        }
        cx=cx-n*dz;
        }
        void scene_translate_y(float dz,int n) 
        {
        for(int i = 0; i < trianglestodraw.size(); ++i) 
        {
            trianglestodraw[i].translate_y(dz,n);
        }
        cy=cy-n*dz;
        }
        void x_rotate_scene(int n)
    {
        for(int i=0;i<trianglestodraw.size();i++)
        {

            trianglestodraw[i].translate_centroid(cx,cy,cz);
            trianglestodraw[i].xr_rotate(n);
            trianglestodraw[i].translate_centroid(-cx,-cy,-cz);
        }
    }
    void y_rotate_scene(int n)
    {
        for(int i=0;i<trianglestodraw.size();i++)
        {
            trianglestodraw[i].translate_centroid(cx,cy,cz);
            trianglestodraw[i].yr_rotate(n);
            trianglestodraw[i].translate_centroid(-cx,-cy,-cz);
        }
    }
    void z_rotate_scene(int n)
    {
        for(int i=0;i<trianglestodraw.size();i++)
        {
            trianglestodraw[i].translate_centroid(cx,cy,cz);
            trianglestodraw[i].zr_rotate(n);
            trianglestodraw[i].translate_centroid(-cx,-cy,-cz);
        }
    }
    void scene_centriod()
{
    cx = 0;
    cy = 0;
    cz = 0;

    for (int i=0;i<trianglestodraw.size();i++)
    {
        cx += trianglestodraw[i].p1.p[0]+trianglestodraw[i].p2.p[0]+trianglestodraw[i].p3.p[0];
        cy += trianglestodraw[i].p1.p[1]+trianglestodraw[i].p2.p[1]+trianglestodraw[i].p3.p[1];
        cz += trianglestodraw[i].p1.p[2]+trianglestodraw[i].p2.p[2]+trianglestodraw[i].p3.p[2];
    }
    
    int vertexCount = trianglestodraw.size()*3;
    cx /= vertexCount;
    cy /= vertexCount;
    cz /= vertexCount;
    
    std::cout << cx << " " << cy << " " << cz << std::endl;
}


};



void render(SDL_Renderer* renderer)
{
    scene scene;
    scene.load_object_from_file("mountains.obj");
    scene.populate();
    scene.scene_centriod();
    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
       
           while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) 
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) 
            {
                switch (event.key.keysym.sym) 
                {
                    case SDLK_UP:

                        scene.x_rotate_scene(1);
                       
                        break;
                    case SDLK_DOWN:
                        scene.x_rotate_scene(-1);
                        
                        break;
                    case SDLK_RIGHT:
                        scene.y_rotate_scene(1);
                        break;
                    case SDLK_LEFT:
                       scene.y_rotate_scene(-1);
                        break;
                    case SDLK_8:
                        scene.z_rotate_scene(1);
                        break;
                    case SDLK_2:
                        scene.z_rotate_scene(-1);
                        
                        break;
                    case SDLK_w:
                    
                        scene.scene_translate_z(0.1,1);
                        
                       
                        break;
                    case SDLK_s:
                        scene.scene_translate_z(0.1,-1);
                        
                      
                        break;
                    case SDLK_a:
                        scene.scene_translate_x(0.1,1);
                        
                      
                        break;
                    case SDLK_d:
                        scene.scene_translate_x(0.1,-1);
                       
                    
                  
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 200,0,1,255);
        
        //cube.render_cube(renderer);
        //t.draw_triangle(renderer);
        scene.render_scene(renderer);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
    }
}
int main(int argv,char** args)
{
        SDL_Window* window =nullptr;
        SDL_Renderer* renderer=nullptr;

        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(SCENE_LENGTH,SCENE_WIDTH, 0, &window, &renderer);
        render(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
        SDL_RenderClear(renderer);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

    return 0;
}