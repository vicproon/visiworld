#ifndef __MARKUP_H
#define __MARKUP_H

#include <deque>
#include <string>

#include "streetglass/framedata.h" // ������, ������������ ��� ����������� �� �����
#include "streetglass/frameproc.h" // ��������� �����

#include "kitti.h"

class Markup
{
protected:
  Markup(bool iskitti_ = false);
  std::vector< FrameData > marked_frames; /// ��������������� � video <===> [iframe]

///////////////////////////////////// video -- ������ ��������
protected:
  bool loadVideo( const std::string &_video_file_name); // �������� ����������� � �������� ������ �������� 
  bool readFrame( int pos ); // ��������� ����������� ����

protected: // video properties, initialized by loadVideo()
  cv::VideoCapture video;
  std::string video_file_path; // full path+name
  std::string video_file_name; // name+extension
  // video properties
  double fps; // = video.get( CV_CAP_PROP_FPS );
  int frames; // = int( video.get( CV_CAP_PROP_FRAME_COUNT ) );
  int frame_width; // = int( video.get( CV_CAP_PROP_FRAME_WIDTH ) );
  int frame_height; // = int( video.get( CV_CAP_PROP_FRAME_HEIGHT ) );
  cv::Mat frame_image; // ����, �������� �� �����������
  int iframe; // ����� ��������������� ������
  int msec; // ����� ������ � ������������� �� ������ ������
  double frame_time; // ����� ������ � �������� �� ������ ������

/////////////////////////////////////////////// for kitty
protected:
  bool iskitti;
//  bool readKitti(int frame_pos);
  bool setCurFrame(int newIFrame);

//new more elegant way to read kitti
  KittiCapture kCap;

//////////////////////////////////////////////// persistence
protected:
  std::string markup_filename; // file based
public: 



  bool readVideoData( 
    cv::FileStorage& fs, 
    std::vector< FrameData >& frames
    );
  bool writeVideoData( 
    cv::FileStorage& fs, 
    std::vector< FrameData >& frames
    );

  bool saveFrameObjectsImages(); // F4

  // visibank:
  bool saveFrameObjectImage( int iobj );
  bool deleteFrameObjectImage( int iobj ); // on undo
  std::string makeFrameObjectImageName( int iframe, const cv::Rect& objRoi, int iobj, 
    const char* szObjType, bool ensureFolder = true );
};


int trackRectangle( cv::VideoCapture& cap, cv::Rect& rect, 
          int nframes, std::vector< cv::Rect >& result ); 


#endif // __MARKUP_H
