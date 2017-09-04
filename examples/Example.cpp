#include "ModworksSDK.h"

int files_downloaded = 0;
int files_to_download = 4;
bool email_request_finished = false;
bool email_exchange_finished = false;
modworks::SDK* mworks;

void onEmailRequest(int result)
{
  if(result == 200)
  {
    cout<<"Code sent!"<<endl;
  }else
  {
    cout<<"Error sending code"<<endl;
  }
  email_request_finished = true;
}

void onExchange(int result)
{
  if(result == 200)
  {
    cout<<"Code exchanged!"<<endl;
  }else
  {
    cout<<"Error exchanging code"<<endl;
  }
  email_exchange_finished = true;
}

void onThumbnailDownloaded(int result,  modworks::Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download thumb successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModInstalled(int result,  modworks::Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download file successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModsGet(vector<modworks::Mod*> mods)
{
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
    cout<<mods[i]->summary<<endl;
    mods[i]->downloadLogoThumbnail(&onThumbnailDownloaded);
    mods[i]->download("mod_directory",&onModInstalled);
  }
}


int main(void)
{
  mworks = new modworks::SDK(/*game_id*/7, /*api_key*/"e91c01b8882f4affeddd56c96111977b");

/*
  mworks->emailRequest("ahmed.hn.43@gmail.com",&onEmailRequest);
  while(!email_request_finished);
  string security_code;
  cout<<"Please enter the 5 digit security code: ";
  cin>>security_code;
  cout<<"Sending code"<<endl;
  mworks->emailExchange(security_code,&onExchange);
  while(!email_exchange_finished);
  */

  mworks->addMod( /*Mod param*/
                  "test22",
                  "http://hello.com",
                  "test test test test test test test test test test test test test test test",
                  "logo.png",
                  /*File param*/
                  "dir/moddir",
                  "0.0.1",
                  "This is a changelog text");
  //mworks->getMods(&onModsGet);
  while(files_downloaded<files_to_download);

  return 0;
}
