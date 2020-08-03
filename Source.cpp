#include<vector>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

class Product {
	string nameProduct;
	double priceProduct;
	int quanituProduct;
public:
	Product() = default;
	Product(const string&nameProduct, const double&priceProduct, const int&quanituProduct) {
		setName(nameProduct);
		setPrice(priceProduct);
		setQuanitu(quanituProduct);
	}

	const double& getPrice() {
		return priceProduct;
	}
	const int& getQuanitu() {
		return quanituProduct;
	}
	string getName() {
		return nameProduct;
	}
	void setPrice(const double&priceProduct) {
		this->priceProduct = priceProduct;
	}
	void setQuanitu(const int &quanituProduct) {
		this->quanituProduct = quanituProduct;
	}
	void setName(const string&nameProduct) {
		this->nameProduct = nameProduct;
	}
	void print() {
		cout << nameProduct << endl;
		cout << priceProduct << endl;
		cout << quanituProduct << endl;
	}

	void writerr(Product&product, const string&fname) {
		ofstream fout;
		fout.open(fname, ofstream::app);
		if (!fout.is_open()) {
			cout << "eroor open file";
		}
		else {
			cout << "file oopen" << endl;
			fout << nameProduct<<endl;
			fout << priceProduct<<endl;
			fout << quanituProduct << endl;
		}
		fout.close();
	}
	void reaaad(const string&fname) {
		ifstream fin;
		fin.open(fname);
		if (!fin.is_open()) {
			cout << "eroor file not open" << endl;
		}
		else {
			cout << "file open" << endl;
			string str;
			while (!fin.eof()) {
				str = "";
				getline(fin, str);
				cout << str << endl;
			}
		}
	}
	static void write(Product&product, const string&fname) {
		ofstream file;
		file.open(fname, ios_base::binary);
		if (!file) {
			cerr << "not open";
			return;
		}
		size_t length = product.getName().size();

		file.write(reinterpret_cast<char*>(&length), sizeof(length));
		file.write(product.getName().c_str(), length);
		file.write(reinterpret_cast<const char*>(&product.getPrice()), sizeof(product.getPrice()));
		file.write(reinterpret_cast<const char*>(&product.getQuanitu()), sizeof(product.getQuanitu()));
		file.close();
	}
	static Product read(const string&fname) {
		string result;
		double price;
		int quanitu;
		ifstream file(fname, ios_base::binary);
		if (!file.is_open()) {
			cerr << "eroor open";
			return Product();
		}
		size_t length;
		file.read(reinterpret_cast<char*>(&length), sizeof(length));
		result.resize(length);
		file.read(const_cast<char*>(result.c_str()), length);
		file.read(reinterpret_cast<char*>(&price), sizeof(price));
		//file.read(reinterpret_cast<char*>(&quanitu), sizeof(quanitu));
		return Product(result, price, quanitu);
	}

};
int main() {

	
	
	Product product("Salts", 12.50, 10);
	product.print();
	string fname = "product.dat";
	Product::write(product, fname);
	cout << "Reaad binary" << endl;
	Product a1;
	a1 = Product::read(fname);
	a1.print();

	string fnames = "pro.txt";
	product.writerr(product, fnames);
	cout << "readd txt" << endl;
	product.reaaad(fnames);
	system("pause");
	return 0;
}