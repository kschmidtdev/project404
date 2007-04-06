/**
 * File: SoundManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added StopAllPlayback, made playback functions safer
 * Karl Schmidt, February 11 2007 | Added calls to stop playing music before shutting down
 * Karl Schmidt, February 11 2007 | Correctly cleared the singleton instance in Shutdown()
 * Karl Schmidt, February 10 2007 | Initial creation of the class
 * Karl Schmidt, March 13 2007    | Added support for sound subsystem disabling
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage
 * Mike Malyuk, March 24 2007     | Added code for RTAudio real time output.
 * Karl Schmidt, March 24 2007    | Renamed some variables to match coding standard, fixed return 03 problem.
 * Karl Schmidt, March 26 2007    | Added volume control functionality for both SDL_Mixer and RTAudio playback
 * Mike Malyuk,  March 27 2007    | Added more try and catches to be more uniform on RtAudio
 * Mike Malyuk,  March 28 2007    | Added stereo back in. Will be utilized later.
 * Mike Malyuk,  March 30 2007    | Added verbosity for logging.
 * Mike Malyuk,  March 31 2007    | Added another short fix
 * Karl Schmidt, April 1 2007     | Rearranged the order of functions and now stopmPing/starting stream instead of
 *                                  killing thread and making a new one every time a new sound is played
 * Mike Malyuk,  April 1 2007     | Huge overhaul, sounds now play from left/right speakers, plays an actual attack, GIGANTIC generation function
 * Karl Schmidt, April 2 2007     | Memory leak fix
 * Mike Malyuk,  April 2 2007     | Added dynamic sound for attack.
 * Mike Malyuk,  April 2 2007     | Added commenting, realized I had been writing out files causing massive slow down. Removed.
 */



#include "SoundManager.h"                                // class implemented
#include <math.h>
#include <Logger.h>
#include <util.h>
#include "BiQuad.h"
#include <cstdlib>
#include <ctime>
typedef float  MY_TYPE;
#define FORMAT RTAUDIO_FLOAT32

#define BASE_RATE 0.005
#define TIME   1.0
/////////////////////////////// PUBLIC ///////////////////////////////////////

namespace
{
    /*static double RTAUDIO_SCALE = 1.0;

    static int cosine(char *buffer, int buffer_size, void *data)
    {
        int i, j;
        static int chans = 2;
        static int times = 0;
        MY_TYPE *my_buffer = (MY_TYPE *) buffer;
        double *my_data = (double *) data;
        MY_TYPE sinval = 0;
        static int n = 0;
        if (times == 1)
        {
            LogInfo("Bad case because of cancel");
            times = 0;
        }
        for (i=0; i<buffer_size; i++)
        {
            sinval = (SoundManager::GetInstance()->GetSoundArr())[n];
            n++;
            if (n > 44100)
            {
                n = 0;
                times++;
                break;
            }
            for (j=0; j<chans; j++)
            {
                *my_buffer++ = (MY_TYPE) (my_data[j] * RTAUDIO_SCALE);
                if(!(SoundManager::GetInstance()->GetLeft()))
                {
                    if(j == 1)
                    {
                        if(n < 11025)
                        {
                            my_data[j] = sinval*((44100-4*n)/44100.0);
                        }
                        else
                        {
                            my_data[j] = 0;
                        }
                    }
                    else
                    {
                        if(n < 11025)
                        {
                            my_data[j] = sinval*((4*n)/44100.0);
                        }
                        else
                        {
                            my_data[j] = sinval;
                        }
                    }
                }
                else
                {
                    if(j == 1)
                    {
                        if(n < 11025)
                        {
                            my_data[j] = sinval*((4*n)/44100.0);
                        }
                        else
                        {
                            my_data[j] = 0;
                        }
                    }
                    else
                    {
                        if(n < 11025)
                        {
                            my_data[j] = sinval*((44100-4*n)/44100.0);
                        }
                        else
                        {
                            my_data[j] = sinval;
                        }
                    }
                }
            }
        }
        if (times == 1)
        {
            LogInfo("Normal throw back");
            times = 0;
            return 1;
        }
        return 0;
    }*/
}

//============================= LIFECYCLE ====================================

SoundManager* SoundManager::_instance = 0;

SoundManager* SoundManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new SoundManager();
    }
    return _instance;
}

SoundManager::~SoundManager()
{
    // stub
}// ~SoundManager

void SoundManager::Initialize( const bool isEnabled )
{
    mIsEnabled = isEnabled;
    if( mIsEnabled )
    {

        LogInfo( "Beginning SoundManager initialization..." );
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
        {
            LogCritical( std::string("Mix_OpenAudio: ") + std::string(Mix_GetError()) );
            tacAssert( false ); // this should never happen
            return;
        }
        Mix_AllocateChannels( 1 );
        SetVolumeLevel( mCurVolumeLevel );
        /*int buffer_size, fs, device = 0;

        mAudioData = new double[2];
        fs = 44100;
        // Open the realtime output device
        buffer_size = 1024;
        try
        {
            mRTAudio = new RtAudio(device, 2, 0, 0,
                                FORMAT, fs, &buffer_size, 4);
        }
        catch (RtError &error)
        {
            LogInfo("Error loading RtAudio device");
            error.printMessage();
            exit(EXIT_FAILURE);
        }
        try
        {
            mRTAudio->setStreamCallback(&cosine, (void *)mAudioData);
            mRTAudio->startStream();
            mRTAudio->stopStream();
        }
        catch (RtError &error)
        {
            error.printMessage();
        }
        // TODO: Make functions for this or something
        mSound = new double[44100];
        for(int i = 0; i < 44100; i++)
        {
            mSound[i] = 0;
        }*/

        LogInfo( "SoundManager initialized successfully." );
    }
}

void SoundManager::Shutdown()
{
    if( mIsEnabled )
    {
        LogInfo( "Beginning SoundManager shut down..." );

        StopAllPlayback();

        Mix_CloseAudio();

        /*delete[] mSound;
        try
        {
        // Stop and close the stream
            mRTAudio->stopStream();
            mRTAudio->closeStream();
        }
        catch (RtError &error)
        {
            LogInfo("Borked on closing RtAudio");
            error.printMessage();
        }

        if( mRTAudio )
        {
            LogInfo("We believe mRTAudio existed");
            delete mRTAudio;
            LogInfo("mRTAudio deleted");
            mRTAudio = NULL;
        }
        if( mAudioData )
        {
            LogInfo("mAudioData existed in deletion");
            delete[] mAudioData;
            LogInfo("mAudioData deleted");
            mAudioData = NULL;
        }*/
    }

    delete _instance;
    _instance = NULL;

    if( mIsEnabled )
    {
        LogInfo( "SoundManager shut down successfully." );
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SoundManager::PlaySoundSample( Mix_Chunk* toPlay, const bool looping )
{
    if( mIsEnabled )
    {
        tacAssert( toPlay );
        if( toPlay )
        {
            Mix_PlayChannel( -1, toPlay, looping ? -1 : 0 );
        }
        else
        {
            LogError( "Attempting to play invalid sound (NULL)" );
        }
    }
}

void SoundManager::PlayMusic( Mix_Music* toPlay, const bool looping )
{
    if( mIsEnabled )
    {
        tacAssert( toPlay );
        if( toPlay )
        {
            Mix_PlayMusic( toPlay, looping ? -1 : 0 );
        }
        else
        {
            LogError( "Attempting to play invalid music (NULL)" );
        }
    }
}

void SoundManager::PlayRTAUDIO()
{
    /*if( mIsEnabled )
    {

        LogInfo("Before stopStream");
        mRTAudio->stopStream();
        try
        {
            //LogInfo("Before setStreamCallback");
            //mRTAudio->setStreamCallback(&cosine, (void *)mAudioData);
            LogInfo("Before startStream");
            mRTAudio->startStream();
        }
        catch (RtError &error)
        {
            LogInfo("Errored");
            error.printMessage();
        }
    }*/
}

void SoundManager::StopAllPlayback()
{
    if( mIsEnabled )
    {
        Mix_HaltChannel(-1);
        Mix_HaltMusic();
    }
}

void SoundManager::SetVolumeLevel( const VOLUME_LEVEL newVolumeLevel )
{
    if( mIsEnabled )
    {
        const int volumeStep = MIX_MAX_VOLUME / VL_MAX;
        Mix_Volume( -1, volumeStep * newVolumeLevel );
        Mix_VolumeMusic( volumeStep * newVolumeLevel );

        //RTAUDIO_SCALE = (1.0 / static_cast<double>(VL_MAX)) * static_cast<double>( newVolumeLevel );

        mCurVolumeLevel = newVolumeLevel;
    }
}

const SoundManager::VOLUME_LEVEL SoundManager::GetVolumeLevel() const
{
    return mCurVolumeLevel;
}

/*std::vector<double> SoundManager::CalcHanning(int m,int n)
{
    std::vector<double> w;
    for(int i = 1; i <= m; i++)
    {
        w.push_back(.5*(1 - cos((2*mPi*i)/(n+1.0))));
    }
    return w;
}

std::vector<double> SoundManager::Hanning(int impulse)
{
    int half;
    std::vector<double> w;
    if(impulse%2 == 0)
    {
        half = impulse/2;
        w = CalcHanning(half, impulse);
        std::vector<double> temp;
        for(std::vector<double>::iterator witer = w.end(); witer != w.begin(); witer--)
        {
            temp.push_back((*witer));
        }
        for(std::vector<double>::iterator titer = temp.begin(); titer != temp.end(); titer++)
        {
            w.push_back((*titer));
        }
    }
    else
    {
        half = (impulse+1)/2;
        w = CalcHanning(half, impulse);
        std::vector<double> temp;
        for(std::vector<double>::iterator witer = (w.end()-1); witer != w.begin(); witer--)
        {
            temp.push_back((*witer));
        }
        for(std::vector<double>::iterator titer = temp.begin(); titer != temp.end(); titer++)
        {
            w.push_back((*titer));
        }
    }
    return w;
}
void SoundManager::SetSoundArray(double tau)
{
    if(!mIsEnabled)
    {
        return;
    }
    //outside valid values for attack set to max Attack tau
    if(tau > 1.2)
    {
        tau = 1.2;
    }
    //outside valid values for attack set to min Attack tau
    if(tau < .025)
    {
        tau = .025;
    }
    std::cout << tau << std::endl; //print out for study
	std::vector<double> fc; //store frequencies
	std::vector<double> Q; //store quality factor for BW
	std::vector<double> G; //store gain

	//pushing back lazily
	fc.push_back(118.0);
	fc.push_back(1517.0);
	fc.push_back(2900.0);
	fc.push_back(3350.0);
	fc.push_back(3546.0);
	fc.push_back(3744.0);
	fc.push_back(3957.0);
	fc.push_back(4508.0);
	fc.push_back(4772.0);
	fc.push_back(5008.0);
	fc.push_back(5133.0);
	fc.push_back(5451.0);
	Q.push_back(1.0);
	Q.push_back(2.0);
	Q.push_back(2.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(100.0);
	Q.push_back(150.0);
	G.push_back(1.7);
	G.push_back(.75);
	G.push_back(.5);
	G.push_back(.95);
	G.push_back(.5);
	G.push_back(.5);
	G.push_back(.5);
	G.push_back(.75);
	G.push_back(.5);
	G.push_back(.5);
	G.push_back(.5);
	G.push_back(1);
	std::vector<double> Bw; //resulting bandwidth
	std::vector<double>::iterator Qiter;
	for(std::vector<double>::iterator fciter = fc.begin(), Qiter = Q.begin(); fciter != fc.end() && Qiter != Q.end(); fciter++, Qiter++ )
	{
	    //Calculate Bw for each frequency passed
	    Bw.push_back((*fciter)/(*Qiter));
	}
	std::vector<double> R; //Setting function for desired BW
	for(std::vector<double>::iterator Bwiter = Bw.begin(); Bwiter != Bw.end(); Bwiter++)
	{
        R.push_back(exp(-mPi*(*Bwiter)*mT));
	}
	//Calculate hanning window
	std::vector<double> w = Hanning((int)(.05*44100));
	std::vector<double> wfin;
	for(std::vector<double>::iterator witer = w.begin(); (int)wfin.size() < ((int)round(w.size()/2.0)); witer++)
	{
	    //only push back half the window
        wfin.push_back((*witer));
	}

    std::vector<double> ex; // create exponential envelope
    for(double i = 0.0; i < 1; i = i + (1/mFS))
    {
        ex.push_back(exp(-i/tau)); //dynamicnism here!
    }
    srand ( time(NULL) );

    std::vector<double> random;
    for(int i = 0; i < mFS; i++)
    {
        //randomly place negatives
        if(rand()%2 == 0)
        {
            random.push_back(rand()/(RAND_MAX*1.0));
        }
        else
        {
            random.push_back(-rand()/(RAND_MAX*1.0));
        }
    }
    std::vector<double> env = wfin;
    for(std::vector<double>::iterator exiter = ex.begin(); env.size() < mFS; exiter++)
    {
        //push back til we fill with 44100 samples on envelope
        env.push_back((*exiter));
    }
	std::vector<double>::iterator enviter;
    std::vector<double> xn; //get x values and put up against noise
	for(std::vector<double>::iterator raniter = random.begin(), enviter = env.begin(); raniter != random.end() && enviter != env.end(); raniter++, enviter++ )
	{
	    xn.push_back((*raniter)*(*enviter));
	}
	//int i = 1;
    /*for(std::vector<double>::iterator xniter = xn.begin(); xniter != xn.end(); xniter++)
    {
        std::cout << i << ": " << (*xniter) << std::endl;
        i++;
    }*/

    /*B[0] = 1;
    B[1] = 0;
    B[2] = -(*R.begin());
    A[0] = 1;
    A[1] = -2*(*R.begin())*cos(2*mPi*(*fc.begin())*mT);
    A[2] = (*R.begin())*(*R.begin());

    BiQuad object(B, A, 3, (*G.begin()));*/
/*    std::vector<double>::iterator giter = G.begin();
    BiQuad* BiQuads = new BiQuad[12];
    int i = 0;
    std::vector<double>::iterator fciter = fc.begin();
    for(std::vector<double>::iterator riter = R.begin(); riter != R.end(); riter++, giter++, fciter++)
    {
        //Setting up for filtering
        double* B = new double[3];
        double* A = new double[3];
        //x(n) - Rx(n-2) + 2*R*cos(2*pi*fc*mT)
        B[0] = 1;
        B[1] = 0;
        B[2] = -(*riter);
        A[0] = 1;
        A[1] = 2*(*riter)*cos(2*mPi*(*fciter)*mT);
        A[2] = (*riter)*(*riter);
        BiQuads[i].Set(B, A, 3, (*giter));
        i++;
        delete[] B;
        delete[] A;
    }
    /*
    double* result = new double[44100];
    i = 0;
    for(std::vector<double>::iterator xiter = xn.begin(); xiter != xn.end(); xiter++)
    {
        result[i] = object.tick((*xiter));
        i++;
    }
    for(int b = 0; b < 44100; b++)
    {
        cout << b+1 << ": " << result[b] << endl;
    }*/
    //set up an array of arrays
/*    double** myArray = new double*[12];

    if (myArray != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            myArray[i] = new double[44100];
        }
    }
    i = 0;
    for(int b = 0; b < 12; b++)
    {
        for(std::vector<double>::iterator xiter = xn.begin(); xiter != xn.end(); xiter++)
        {
            myArray[b][i] = BiQuads[b].tick((*xiter)); //store each generated to one line on array
            i++;
        }
        i = 0;
    }
    // to delete those:
    double* result = new double[44100];

    for(int b = 0; b < 44100; b++)
    {
        result[b] = 0;
    }

    for(int a = 0; a < 12; a++)
    {
        for(int b = 0; b < 44100; b++)
        {
            result[b] = result[b] + myArray[a][b];
        }
    }
    double max = 0;
    for(int b = 0; b < 44100; b++)
    {
        if(fabs(result[b]) > max)
        {
            max = fabs(result[b]);
        }
    }
    for(int b = 0; b < 44100; b++)
    {
        result[b] = .8*(result[b]/max);
    }
    for (int i = 0; i < 12; i++)
    {
        delete[] myArray[i];
        myArray[i] = 0;
    }
    for(int b = 0; b < 44100; b++)
    {
        mSound[b] = result[b];
    }
    delete[] myArray;
    delete[] result;
    delete[] BiQuads;
    myArray = 0;
}
*/
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

SoundManager::SoundManager(void)
: mIsEnabled( true ),
//  mRTAudio( NULL ),
//  mAudioData( NULL ),
  mCurVolumeLevel( VL_MODERATE ),
  mPi(3.141592653589793),
  mFS(44100),
  mT(1/44100.0),
  mLeft(true)
{
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
