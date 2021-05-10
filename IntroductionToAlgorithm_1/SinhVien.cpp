#include "SinhVien.h"

SinhVien::SinhVien() {
	TenSV = "";
	MaSV = "";
	Lop = "";
	NamSinh = "";
	DiemTB = 0;
}
SinhVien::SinhVien(string tensv, string masv, string lop, string namsinh, float dtb) {
	TenSV = tensv;
	MaSV = masv;
	Lop = lop;
	NamSinh = namsinh;
	DiemTB = dtb;
}
string SinhVien::getTenSV() {
	return TenSV;
}
void SinhVien::setTenSV(string tensv) {
	TenSV = tensv;
}
string SinhVien::getMaSV() {
	return MaSV;
}
void SinhVien::setMaSV(string masv) {
	MaSV = masv;
}
string SinhVien::getLop() {
	return Lop;
}
void SinhVien::setLop(string lop) {
	Lop = lop;
}
string SinhVien::getNamSinh() {
	return NamSinh;
}
void SinhVien::setNamSinh(string namsinh) {
	NamSinh = namsinh;
}
float SinhVien::getDiemTB() {
	return DiemTB;
}
void SinhVien::setDiemTB(float dtb) {
	DiemTB = dtb;
}

void SinhVien::NhapThongTin(int a) {

	cin.ignore();
	CreateText(5, a + 1, MAUCHU, "Ho ten sinh vien : ");
	getline(cin, TenSV);

	CreateText(5, a + 2, MAUCHU, "Ma sinh vien: ");
	getline(cin, MaSV);

	CreateText(5, a + 3, MAUCHU, "Lop sinh vien: ");
	getline(cin, Lop);

	CreateText(5, a + 4, MAUCHU, "Ngay thang nam sinh : ");
	getline(cin, NamSinh);

	CreateText(5, a + 5, MAUCHU, "Diem trung binh: ");
	cin >> DiemTB;
	cout << endl;
}

void SinhVien::XuatThongTin()
{
	cout << setw(20) << MaSV << setw(30) << TenSV << setw(10) << Lop << setw(20) << NamSinh << setw(10) << DiemTB << endl;
}


void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD menu = { x, y };
	SetConsoleCursorPosition(h, menu);
}


void textcolor(WORD color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void CreateText(int posX, int posY, int textColor, std::string message)
{
	gotoxy(posX, posY);
	textcolor(textColor);
	cout << message;
	textcolor(223);
}
