#include <iostream>
#include <vector>
// we create struct Pixel to store r g b
struct Pixel { uint8_t r; uint8_t g; uint8_t b; };
class Image{
    private:
    int width_;
    int height_;
    int channels_;
    std::vector<uint8_t> data_;

    public:
    Image(int w,int h,int c)
    : width_(w), height_(h), channels_(c), data_(w*h*c)
    {
    }

    /*
    setPixel takes the buffer by reference (no copy). The vector manages memory via RAII. and checks if the pixel is in bounds,
    if it is then we call pixelIndex to get the base. Then we set each pixel indexing by off sets 0,1,2.
    */
    bool setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b){
        if(channels_ < 3) {return false;}
        if (0 > x or x >= width_ or 0 > y or y >= height_){
            std::cout<<"X or Y out of bounds"<<std::endl;
            return false;
        }
        else{
            int base = pixelIndex(x, y);
            data_[base] = r;
            data_[base + 1] = g;
            data_[base + 2] = b;
            return true;
            }
    }

    /*
    Simple helper function meant to return base
    */
    int pixelIndex(int x, int y) const {
    // compute base byte index in the 1D buffer for (x,y).
    int base = (y * width_ + x) * channels_;
    return base;
    }

    /*
    getPixel will return each channel within the pixel value assuming a RGB channel.
    with a constant reference so buffer does not get overridden within the function.
    */
    Pixel getPixel(int x, int y) const {
    if(channels_ < 3) {return {0,0,0};}
    if (0 > x or x >= width_ or 0 > y or y >= height_){
        std::cout<<"X or Y out of bounds"<<std::endl;
        Pixel p = {0,0,0};
        return p;
    }
    int base = pixelIndex(x, y);
    uint8_t r = data_[base];
    uint8_t g = data_[base + 1];
    uint8_t b =data_[base + 2];
    Pixel p = {r,g,b};
    return p;
        
    }
    /*
    Inverts every byte in the pixel using auto &v which v represents
    a reference to each byte in the pixel.
    */
    void invert(){
        for(auto &v : data_){
            v = 255 - v;
        }
    }


    /*
    Converts every byte within every pixel to grayscale.
    */
    void toGrayscale(){
        // error check
        if(channels_ < 3) {return;}
        // loop every 3 indexes, which is every pixel
        for (int i = 0; i < data_.size(); i += channels_){
            uint8_t r = data_[i];
            uint8_t g = data_[i + 1];
            uint8_t b = data_[i + 2];
            int gray = (r + g + b) / 3;
            data_[i] = gray;
            data_[i + 1] = gray;
            data_[i +2] = gray;
        }
    }
    /*
    Sets every byte in the image to value.
    */
    void clear(uint8_t value){
        for( int i = 0; i < data_.size(); i++){
            data_[i] = value;
        }
    }
};

int main(){
    Image img(150,100,3);
    img.setPixel(15,5,0,255,0);
    //img.invert();
    img.toGrayscale();
    img.clear(255);
    Pixel p = img.getPixel(15,5);
    std::cout<<static_cast<int>(p.r)<<std::endl;
    std::cout<<static_cast<int>(p.g)<<std::endl;
    std::cout<<static_cast<int>(p.b)<<std::endl;

}

