class vector
{
    private:
        float x,y,z;
    public:
        vector():x(0),y(0),z(0){};
        vector(float x,float y,float z):x(x),y(y),z(z){};
        vector(const vector& other) : x(other.x), y(other.y), z(other.z) {}
        
        void set_vector(float x,float y,float z)
        {
            this->x=x;
            this->y=y;
            this->z=z;
        }
        vector operator * (vector& v)
        {
            vector resultant;
            resultant.x= y * v.z - z * v.y;
            resultant.y= z * v.x - x * v.z;
            resultant.z= x * v.y - y * v.x;
            return resultant;
        }
        vector operator - (vector& v)
        {
            vector resultant;
            resultant.x=x-v.x;
            resultant.y= y-v.y;
            resultant.z= z-v.z;
            return resultant;
        }
        void normalize(float f)
        {
            x=x/f;
            y=y/f;
            z=z/f;
        }
        float dot_product(vector& v)
        {
            return x*v.x+y*v.y+z*v.z;
        }
        float mag()
        {
            return sqrt(x*x+y*y+z*z);
        }
        friend class triangle;
};
