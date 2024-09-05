#include<iostream>
#include<SDL2/SDL.h>
#include<cmath>
#include<vector>
#include"matrix.h"
#include"vector.h"
#include<algorithm>
#define SCENE_LENGTH 1000
#define SCENE_WIDTH 700

#define FOV 1.047f


class shape
{
    protected:
    float R,G,B;
    
    float theta=0.1;
    

    
    public:
        shape() : R(0), G(0), B(0){};
        shape(int R,int G,int B)
        {
            this->R=R;
            this->G=G;
            this->B=B;
            
        }
        void get_color()
        {
            std::cout<<"RGB color = "<<"("<<R<<","<<G<<","<<B<<")"<<std::endl;
        }
        float return_theta(int i)
        {
            return i*theta;
        }
    
};
class triangle:public shape
{
    matrix p1,p2,p3,p1_proj,p2_proj,p3_proj,mp;
    vector normal,a,b;
    
    void create_p_m()
{

    float f = 1.0f / tan(FOV / 2.0f);
    float aspect =SCENE_LENGTH / SCENE_WIDTH;
    float z_near = 0.1;
    float z_far = 1000;
    float lambda = z_far / (z_far - z_near);

   float elem[] = {
        f *aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, z_far / (z_far - z_near), -z_far*z_near / (z_far - z_near),
        0, 0,1, 0
    };

    mp.set_values( elem);
}
    public:
        triangle():p1(4,1),p2(4,1),p3(4,1),p1_proj(4,1),p2_proj(4,1),p3_proj(4,1),mp(4,4){}
        triangle(float pe1[],float pe2[],float pe3[],Uint8 r,Uint8 b,Uint8 g):p1(4,1),p2(4,1),p3(4,1),p1_proj(4,1),p2_proj(4,1),p3_proj(4,1),mp(4,4)
        {
            this->R=r;
            this->G=g;
            this->B=b;

            this->p1.set_values(pe1);
            this->p2.set_values(pe2);
            this->p3.set_values(pe3);
        
            
            

            
        }
        ~triangle()
        {
        }
    
    triangle(const triangle& other) {
    p1 = matrix(other.p1);
    p2 = matrix(other.p2);
    p3 = matrix(other.p3);
    p1_proj = matrix(other.p1_proj);
    p2_proj = matrix(other.p2_proj);
    p3_proj = matrix(other.p3_proj);
    mp = matrix(other.mp);
    R = other.R;
    G = other.G;
    B = other.B;
    normal = vector(other.normal.x, other.normal.y, other.normal.z);
    a = vector(other.a.x, other.a.y, other.a.z);
    b = vector(other.b.x, other.b.y, other.b.z);
}
        void get_data(float a[],float b[],float c[],Uint8 r,Uint8 g,Uint8 bl)
        {
            p1.set_values(a);
            p2.set_values(b);
            p3.set_values(c);
            R=r;
            B=bl;
            G=g;

        }
    


       void print()
       {
        p1.print();p2.print();p3.print();       }
        void translate_centroid(float x,float y,float z)
        {
            p1.p[0]=p1.p[0]-x;
            p1.p[1]=p1.p[1]-y;
            p1.p[2]=p1.p[2]-z;

            p2.p[0]=p2.p[0]-x;
            p2.p[1]=p2.p[1]-y;
            p2.p[2]=p2.p[2]-z;

            p3.p[0]=p3.p[0]-x;
            p3.p[1]=p3.p[1]-y;
            p3.p[2]=p3.p[2]-z;
        }
        void translate_x(float x,int i)
        {
            p1.p[0]=p1.p[0]-x*i;
            p2.p[0]=p2.p[0]-x*i;
            p3.p[0]=p3.p[0]-x*i;
        }
        void translate_y(float x,int i)
        {
            p1.p[1]=p1.p[1]-x*i;
            p2.p[1]=p2.p[1]-x*i;
            p3.p[1]=p3.p[1]-x*i;
        }
        void translate_z(float x,int i)
        {
            p1.p[2]=p1.p[2]-x*i;
            p2.p[2]=p2.p[2]-x*i;
            p3.p[2]=p3.p[2]-x*i;
        }

        void draw_triangle(SDL_Renderer* renderer) 
        {
            
            a.x=p2.p[0]-p1.p[0];
            a.y=p2.p[1]-p1.p[1];
            a.z=p2.p[2]-p1.p[2];

            b.x=p3.p[0]-p1.p[0];
            b.y=p3.p[1]-p1.p[1];
            b.z=p3.p[2]-p1.p[2];

            normal=a*b;
            float normal_mag=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
            normal.x=normal.x/normal_mag;
            normal.y=normal.y/normal_mag;
            normal.z=normal.z/normal_mag;
    if((normal.x*p1.p[0]+normal.y*p1.p[1]+normal.z*p1.p[2])<0){
        create_p_m();
        p1_proj=mp*p1;
        p2_proj=mp*p2;
        p3_proj=mp*p3;
         if (p1_proj.p[3] <= 0 || p2_proj.p[3] <= 0 || p3_proj.p[3] <= 0) {
        return;
    }

        if (p1_proj.p[3] != 0) { p1_proj = p1_proj / p1_proj.p[3]; }
        if (p2_proj.p[3] != 0) { p2_proj = p2_proj / p2_proj.p[3]; }
        if (p3_proj.p[3] != 0) { p3_proj = p3_proj / p3_proj.p[3]; }


        float screen_x1 = p1_proj.p[0]*SCENE_LENGTH / 2  + SCENE_LENGTH / 2;
        float screen_y1 = p1_proj.p[1]*SCENE_WIDTH / 2  + SCENE_WIDTH / 2;
        float screen_x2 = p2_proj.p[0]*SCENE_LENGTH / 2 + SCENE_LENGTH / 2;
        float screen_y2 = p2_proj.p[1]*SCENE_WIDTH / 2  + SCENE_WIDTH / 2;
        float screen_x3 = p3_proj.p[0]*SCENE_LENGTH / 2  + SCENE_LENGTH / 2;
        float screen_y3 = p3_proj.p[1]*SCENE_WIDTH / 2  + SCENE_WIDTH / 2;

       vector lighting_dir(0,0,-1);
        lighting_dir.normalize(lighting_dir.mag());
        float dot_pro=lighting_dir.dot_product(normal);
        if(dot_pro<0)
        {
            dot_pro=0;
        }
       //float dot_pro=1;


const std::vector< SDL_Vertex > verts =
    {
        { SDL_FPoint{ screen_x1, screen_y1 }, SDL_Color{ static_cast<Uint8>(R*dot_pro), static_cast<Uint8>(G*dot_pro), static_cast<Uint8>(B*dot_pro), 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ screen_x2, screen_y2 }, SDL_Color{ static_cast<Uint8>(R*dot_pro), static_cast<Uint8>(G*dot_pro), static_cast<Uint8>(B*dot_pro), 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ screen_x3, screen_y3 }, SDL_Color{ static_cast<Uint8>(R*dot_pro), static_cast<Uint8>(G*dot_pro), static_cast<Uint8>(B*dot_pro), 255 }, SDL_FPoint{ 0 }, },
    };
     SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
        /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, screen_x1, screen_y1, screen_x2, screen_y2);
        SDL_RenderDrawLine(renderer, screen_x2, screen_y2, screen_x3, screen_y3);
        SDL_RenderDrawLine(renderer, screen_x3, screen_y3, screen_x1, screen_y1);*/
    }
}

        
        void xr_rotate(int i)
        {
            
     
            p1=create_x_rot(shape::return_theta(i))*p1;
            p2=create_x_rot(shape::return_theta(i))*p2;
            p3=create_x_rot(shape::return_theta(i))*p3;
          
            
        
        }
        void yr_rotate(int i)
        {
            
          
            p1=create_y_rot(shape::return_theta(i))*p1;
            p2=create_y_rot(shape::return_theta(i))*p2;
            p3=create_y_rot(shape::return_theta(i))*p3;
        
        
        }
        void zr_rotate(int i)
        {

            
            
            p1=create_z_rot(shape::return_theta(i))*p1;
            p2=create_z_rot(shape::return_theta(i))*p2;
            p3=create_z_rot(shape::return_theta(i))*p3;
         
        
        }
        friend class scene;
        friend class cube;
};
