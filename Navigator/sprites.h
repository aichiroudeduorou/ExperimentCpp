#pragma once
#include <string>
#include "models.h"
#include "resource.h"
namespace FZJ {
    using std::wstring;
    class Sprite {
    public:
        Sprite() {

        }
        ~Sprite() {
            if (Actor) {
                Actor->SetSignal(nullptr);
            }
        }
        bool SetSignal(Sprite* p) {
            signal = p;
            return true;
        }
        bool SetActor(Sprite* p) {
            Actor = p;
            return true;
        }
        bool OnMouseMove(long _x, long _y) {
            if (signal) {
                visiable = signal->visiable;
                return visiable;
            }
            if (x <= _x && _x <= right && y <= _y && _y <= bottom) {
                visiable = true;
                return true;
            }
            visiable = false;
            return false;
        }
        bool OnMouseLButtonUp(long _x, long _y) {
            if (x <= _x && _x <= right && y <= _y && _y <= bottom) {
                return true;
            }
            return false;
        }
        bool OnMouseRButtonUp(long _x, long _y) {
            if (x <= _x && _x <= right && y <= _y && _y <= bottom) {
                return true;
            }
            return false;
        }
        virtual bool Paint(const CDC& targetDC) = 0;
    public:
        int x = 0, y = 0, height = 0, width = 0;
        int right = 0, bottom = 0;
        Sprite* signal = nullptr;
        Sprite* Actor = nullptr;
        bool visiable = true;
        /*int centerX, centerY;*/
    };


    class LocationSprite :public Sprite {
    public:
        std::vector<Organization*> organizations;
        int locationID;
        double distanceTo(LocationSprite* dest) {
            auto f = [](double x)->double {
                return x * x;
            };
            return std::sqrt(f(x - dest->x) + f(y - dest->y));
        }
       
        LocationSprite(const CString& str, int id) {
            CString tmp(str);
            tmp.Trim();
            auto i = tmp.Find(L'£¬', 0);
            i = i > -1 ? i : tmp.Find(L',', 0);
            auto xstr = tmp.Mid(0, i);
            auto ystr = tmp.Mid(i + 1, tmp.GetLength() - i);
            long _x = _ttoi(xstr);
            long _y = _ttoi(ystr) + 60;
            locationID = id;
            icon.Load(L"Data\\location.png");
            height = icon.GetHeight();
            width = icon.GetWidth();
            y = _y - height;
            x = _x - width / 2;
            right = x + width;
            bottom = y + height;
        }

        bool Paint(const CDC& targetDC) {
            icon.Draw(targetDC, x, y, width, height);
            return true;
        }
    private:
        CImage icon;

    };
}


