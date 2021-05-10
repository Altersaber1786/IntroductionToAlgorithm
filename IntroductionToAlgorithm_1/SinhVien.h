#include<iostream>
#include<windows.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>

#define SINHVIEN 10000
#define MAUCHECK 31
#define MAUCHU 28
#define MAU 15

using namespace std;
class SinhVien {
private:
	string TenSV;

public:
	float DiemTB;
	string NamSinh;
	string Lop;
	string MaSV;
	string getNamSinh();

	void setNamSinh(string namsinh);
	string getTenSV();
	void setTenSV(string tensv);
	string getMaSV();
	void setMaSV(string masv);
	string getLop();
	void setLop(string lop);
	float getDiemTB();
	void setDiemTB(float dtb);
	SinhVien();
	SinhVien(string tensv, string masv, string lop, string namsinh, float dtb);
	void NhapThongTin(int a);
	void XuatThongTin();
};

void gotoxy(int x, int y);

void textcolor(WORD color);
void CreateText(int posX, int posY, int textColor, std::string message);