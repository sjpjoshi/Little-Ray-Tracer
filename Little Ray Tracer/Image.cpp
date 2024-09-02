#include "Image.hpp"

Image::Image() {
	imageX = 0;
	imageY = 0;
	m_Texture = NULL;
	m_renderer = NULL;

} // Image

Image::~Image() {
	if (m_Texture != NULL)
		SDL_DestroyTexture(m_Texture);

} // ~Image

void Image::intialize(const int ImageX, const int ImageY, SDL_Renderer* Renderer) {
	// Resizing image vecs
	m_redChannel.resize  (  ImageX, std::vector<double>(ImageY, 0.0));
	m_greenChannel.resize(  ImageX, std::vector<double>(ImageY, 0.0));
	m_blueChannel.resize (  ImageX, std::vector<double>(ImageY, 0.0));

	// store image size
	imageX = ImageX;
	imageY = ImageY;

	// store the rendere
	m_renderer = Renderer;

	intializeTexture();

} // intialize

void Image::setPixel(const int ImageX, const int ImageY, const double red, const double green, const double blue) {
	m_redChannel.at(ImageX).at(ImageY) = red;
	m_greenChannel.at(ImageX).at(ImageY) = green; 
	m_blueChannel.at(ImageX).at(ImageY) = blue; 

} // setPixel

// function to generate the display
void Image::displayImage() {

	// Compute max values
	computeMaxValues();

	// Allocate memory for a pixel buffer
	Uint32* tempPixels = new Uint32[imageX * imageY];

	// clear pixel buffer
	memset(tempPixels, 0, imageX * imageY * sizeof(Uint32));

	for (int i = 0; i < imageX; ++i) {
		for (int j = 0; j < imageY; ++j) {

			tempPixels[ (j * imageX) + i] = convertColor( m_redChannel.at(i).at(j), m_greenChannel.at(i).at(j), m_blueChannel.at(i).at(j)); // tempPixels

		} // for

	} // for

	// update the texture with the pixel buffer
	SDL_UpdateTexture(m_Texture, NULL, tempPixels, imageX * sizeof(Uint32));

	// Delete the pixel buffer
	delete[] tempPixels;

	// copy the texture to the renderer
	SDL_Rect sourceRect, bounds;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = imageX;
	sourceRect.h = imageY;
	bounds = sourceRect;

	SDL_RenderCopy(m_renderer, m_Texture, &sourceRect, &bounds);

} // displayImage

int Image::getImageX() { return imageX; } // getImageX
int Image::getImageY() { return imageY; } // get ImageY

void Image::intializeTexture() {
	Uint32 redMask, greenMask, blueMask, alphaMask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		redMask = 0xff000000;
		greenMask = 0x00ff0000;
		blueMask = 0x0000ff00;
		alphaMask = 0x000000ff;

	#else
		redMask = 0x000000ff;
		greenMask = 0x0000ff00;
		blueMask = 0x00ff0000;
		alphaMask = 0xff000000;

	#endif

	// delete any previously created texture
	if (m_Texture != NULL)
		SDL_DestroyTexture(m_Texture);

	// create the image that will store the image
	SDL_Surface* tSurface = SDL_CreateRGBSurface(0, imageX, imageY, 32, redMask, greenMask, blueMask, alphaMask);
	m_Texture = SDL_CreateTextureFromSurface(m_renderer, tSurface);
	SDL_FreeSurface(tSurface);

} // intializeTexture

Uint32 Image::convertColor(const double Red, const double Green, const double Blue) {
	// convert the colors to unsigned ints
	unsigned char red = static_cast<unsigned char>  ((Red   / m_MaxRed)   * 255.0);
	unsigned char green = static_cast<unsigned char>((Green / m_MaxGreen) * 255.0);
	unsigned char blue = static_cast<unsigned char> ((Blue  / m_MaxBlue)  * 255.0);

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (red << 24) + (green << 16) + (blue << 8) + 255;

	#else
		Uint32 pixelColor = (255 << 24) + (blue << 16) + (green << 8) + red;

	#endif

	return pixelColor;

} // convertColor

// function to convert colors to Uint32
void Image::computeMaxValues() {
	m_MaxRed = 0.0;
	m_MaxGreen = 0.0;
	m_MaxBlue = 0.0;
	m_OverallMax = 0.0;

	for (int i = 0; i < imageX; ++i) {
		for (int j = 0; j < imageY; ++j) {
			double redValue   = m_redChannel.at(i).at(j); 
			double greenValue = m_greenChannel.at(i).at(j);  
			double blueValue  = m_blueChannel.at(i).at(j);  
			if (redValue > m_MaxRed) 
				m_MaxRed = redValue;

			if (greenValue > m_MaxGreen)
				m_MaxGreen = greenValue;

			if (blueValue > m_MaxBlue)
				m_MaxBlue = blueValue; 

			if (m_MaxRed > m_OverallMax)
				m_OverallMax = m_MaxRed;

			if (m_MaxGreen > m_OverallMax)
				m_OverallMax = m_MaxGreen;

			if (m_MaxBlue > m_OverallMax)
				m_OverallMax = m_MaxBlue; 

		} // for (int j = 0; j < imageY; ++j)

	} // for (int i = 0; i < imageX; ++i)

} // computeMaxValues