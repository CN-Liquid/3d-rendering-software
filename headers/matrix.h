#include<iostream>
#include<cmath>
class matrix
{
    public:
        int row,col;
        float* p;
        
        matrix(){
            p= new float[4]{1};
            row=4;
            col=1;
        };
            matrix(int row,int col):row(row),col(col){
                
                int temp =row*col;
               p= new float[temp]{1};
              
            }
            void print()
            {
             std::cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<" "<<std::endl;
            }
            void set_values(float* values) {
        for (int i = 0; i < row * col; ++i) {
            p[i] = values[i];
        }
    }
            matrix(const matrix& other) : row(other.row), col(other.col) {
    p = new float[row * col];
    for (int i = 0; i < row * col; i++) {
        p[i] = other.p[i];
    }
}  
            void set_matrix(float a,float b,float c)
            {
                p[0]=a;
                p[1]=b;
                p[2]=c;
            }
            

            void update_z(int i)
            {
                p[2]=p[2]+i;
                
            }
            matrix operator /(float f)
            {
                matrix res(row,col);
               for(int i=0;i<row*col;i++)
                {
                    res.p[i]=p[i]/f;
                }
                return res;
            }

            friend matrix operator *(matrix,matrix);
};
matrix operator *(matrix m1,matrix m2)
{
    matrix res(m1.row,m2.col);
    for(int i=0;i<m1.row;i++)
    {
        for(int j=0;j<m2.col;j++)
        {
            res.p[i * m2.col + j] = 0;
            for(int k=0;k<m1.col;k++)
            {

                res.p[i*res.col+j]+=m1.p[i*m1.col+k]*m2.p[k*m2.col+j];
            }
        }
    }
    return res;
}
matrix create_x_rot(float theta)
{
    matrix x_rot(4,4);
     float x_rotate[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, static_cast<float>(cos(theta)), static_cast<float>(-sin(theta)), 0.0f,
    0.0f, static_cast<float>(sin(theta)), static_cast<float>(cos(theta)), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
    x_rot.set_values(x_rotate);
    return x_rot;
}
matrix create_y_rot(float theta)
{
    matrix y_rot(4,4);
    float y_rotate[] = {
    static_cast<float>(cos(theta)), 0.0f, static_cast<float>(sin(theta)), 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    static_cast<float>(-sin(theta)), 0.0f, static_cast<float>(cos(theta)), 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
    y_rot.set_values(y_rotate);
    return y_rot;
}matrix create_z_rot(float theta)
{
    matrix z_rot(4,4);
    float z_rotate[] = {
    static_cast<float>(cos(theta)), static_cast<float>(-sin(theta)), 0.0f, 0.0f,
    static_cast<float>(sin(theta)), static_cast<float>(cos(theta)), 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
    z_rot.set_values(z_rotate);
    return z_rot;
}