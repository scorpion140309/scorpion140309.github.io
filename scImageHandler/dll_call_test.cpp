#define _CRT_SECURE_NO_DEPRECATE
#include <scMetaImg.h>
#include <scImageHandler.h>

#include <windows.h>
#include <cstdio>

typedef const char* ( __stdcall *P_ERROR_MSG )();
typedef int ( __stdcall *P_SET_QALITY )( int qality );
typedef int ( __stdcall *P_SAVE_IMAGE )( const char *img_filename, const scMetaImg *p_meta_img, int img_format_id );
//typedef int ( __stdcall *P_CREATE_IMAGE )( const char *img_filename, scMetaImg ** pp_meta_img );
typedef void * ( __stdcall *P_CREATE_IMAGE )( const char *img_filename );
typedef int ( __stdcall *P_DELETE_IMAGE )( scMetaImg *p_meta_img );

int SaveRaw( const char *filename, const scMetaImg *p_mega_img )
{
	int result = -1;
	std::FILE *fp;

	fp = std::fopen( filename, "wb" );
	if( fp )
	{
		int byte_size;
		byte_size = ( ( p_mega_img->Width() * p_mega_img->Bit() + 7 ) / 8 ) * p_mega_img->Height();
		std::fwrite( p_mega_img->CstImgPtr08( 0 ), byte_size, 1, fp );
		std::fclose( fp );
		result = 0;
	}

	return result;
}

int Test_scImageHandler_DLL( const char *input_imgfile )
{
	const char DLL_PATH[] = "scImageHandler.dll";
	int result = -1;
	HINSTANCE hDLL;

	hDLL = ::LoadLibrary( DLL_PATH );
	if( hDLL )
	{
		P_ERROR_MSG		p_err_msg;
		P_SET_QALITY	p_set_quality;
		P_SAVE_IMAGE	p_save_img;
		P_CREATE_IMAGE	p_create_img;
		P_DELETE_IMAGE	p_delete_img;

		p_err_msg		= reinterpret_cast< P_ERROR_MSG >( ::GetProcAddress( hDLL, "scImageHandler_LastErrorMessage" ) );
		p_set_quality	= reinterpret_cast< P_SET_QALITY >( ::GetProcAddress( hDLL, "scImageHandler_SetQuality" ) );
		p_save_img		= reinterpret_cast< P_SAVE_IMAGE >( ::GetProcAddress( hDLL, "scImageHandler_Save" ) );
		p_create_img	= reinterpret_cast< P_CREATE_IMAGE >( ::GetProcAddress( hDLL, "scImageHandler_Create" ) );
		p_delete_img	= reinterpret_cast< P_DELETE_IMAGE >( ::GetProcAddress( hDLL, "scImageHandler_Delete" ) );

		if( p_err_msg != NULL && p_set_quality != NULL && p_save_img != NULL && p_create_img != NULL && p_delete_img != NULL )
		{
			scMetaImg *p_meta_img = NULL;

			// Load
			p_meta_img = static_cast< scMetaImg * >( ( *p_create_img )( input_imgfile ) );
			if( p_meta_img != NULL )
			{
//SaveRaw( "hoge.raw", p_meta_img );
				// Save
				result = ( *p_save_img )( "output.png", p_meta_img, scImageHandler::FORMAT::PNG );
				result = ( *p_save_img )( "output.bmp", p_meta_img, scImageHandler::FORMAT::BMP );
				result = ( *p_save_img )( "output.tif", p_meta_img, scImageHandler::FORMAT::TIFF );
				result = ( *p_save_img )( "output.gif", p_meta_img, scImageHandler::FORMAT::GIF );
				result = ( *p_save_img )( "output.jpg", p_meta_img, scImageHandler::FORMAT::JPEG );
			}
		}
		::FreeLibrary( hDLL );

	}

	return result;
}

int main( int argc, char **argv )
{
	int result = -1;
	if( argc > 1 )
	{
		result = Test_scImageHandler_DLL( argv[ 1 ] );
	}
	else
	{
		::MessageBox( NULL, "1 or 8 or 24bit RGBâÊëúÇì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB\n(JPGE,PNG,GIF,TIFF,BMP)", "error", MB_OK | MB_ICONERROR );
	}
	return result;
}
