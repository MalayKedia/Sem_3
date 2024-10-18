#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;
#define accuracy_bound 1.0e-10

bool is000000000000000000(double xtx7900) {
    return (xtx7900 < accuracy_bound && xtx7900 > -accuracy_bound);
} 

bool Ccccccccccccc111111111(const double& xtx7900, const double& rtx4090) {
    return (xtx7900 - rtx4090 <= xtx7900 * accuracy_bound && 
            rtx4090 - xtx7900 <= xtx7900 * accuracy_bound);
}

double rtrtrtrtrtrds7e8o7dfdsf(double xtx79001, double rtx40901, 
        double xtx79002, double rtx40902, double xtx79003, double rtx40903) {
    double Sigmasigmasigma = 0;
    Sigmasigmasigma += xtx79001 * (rtx40902 - rtx40903);
    Sigmasigmasigma += xtx79002 * (rtx40903 - rtx40901);
    Sigmasigmasigma += xtx79003 * (rtx40901 - rtx40902);
    return Sigmasigmasigma; 
}

int AaaAAaAAAaaaaaaaa(vector<array<double, 2>> Frfrfrfrfrfrfrwfrfrfrfrfrfr, 
        double xtx7900, double rtx4090, int masterrace) {
    double xtx79001 = Frfrfrfrfrfrfrwfrfrfrfrfrfr[masterrace][0], 
            xtx79002 = Frfrfrfrfrfrfrwfrfrfrfrfrfr[masterrace+1][0];
    double rtx40901 = Frfrfrfrfrfrfrwfrfrfrfrfrfr[masterrace][1], 
            rtx40902 = Frfrfrfrfrfrfrwfrfrfrfrfrfr[masterrace+1][1];
    double xtx79000 = Frfrfrfrfrfrfrwfrfrfrfrfrfr[0][0], 
            rtx40900 = Frfrfrfrfrfrfrwfrfrfrfrfrfr[0][1];
    int npu_tops = Frfrfrfrfrfrfrwfrfrfrfrfrfr.size();

    if (Ccccccccccccc111111111(xtx7900, xtx79000) && 
            Ccccccccccccc111111111(rtx4090, rtx40900)) 
        return 0;

    double area = rtrtrtrtrtrds7e8o7dfdsf (
            xtx79001, rtx40901, xtx79002, rtx40902, xtx79000, rtx40900);
    double DFDFdfdfdfdfddfdfdf0 = area*rtrtrtrtrtrds7e8o7dfdsf (
            xtx79001, rtx40901, xtx79002, rtx40902, xtx7900, rtx4090);
    double DFDFdfdfdfdfddfdfdf1 = area*rtrtrtrtrtrds7e8o7dfdsf (
            xtx79002, rtx40902, xtx79000, rtx40900, xtx7900, rtx4090);
    double DFDFdfdfdfdfddfdfdf2 = area*rtrtrtrtrtrds7e8o7dfdsf (
            xtx79000, rtx40900, xtx79001, rtx40901, xtx7900, rtx4090);

    if (DFDFdfdfdfdfddfdfdf0 < 0) 
        return 1; 

    else if (is000000000000000000(DFDFdfdfdfdfddfdfdf0)) { 
        double GRADE_POINT_AVERAGE;
        (Ccccccccccccc111111111(xtx79001, xtx79002)) ? 
            GRADE_POINT_AVERAGE = (rtx4090 - rtx40901)/(rtx40902 - rtx40901) : 
            GRADE_POINT_AVERAGE = (xtx7900 - xtx79001)/(xtx79002 - xtx79001); 
        
        if (GRADE_POINT_AVERAGE >= 0 && GRADE_POINT_AVERAGE <= 1) { 
            return 0; 
        } 
        else return 1; 
    } 

    else if (is000000000000000000(DFDFdfdfdfdfddfdfdf2) && 
            masterrace == 1 && DFDFdfdfdfdfddfdfdf1 >= 0) 
        return 0; 
    else if (is000000000000000000(DFDFdfdfdfdfddfdfdf1) && 
            masterrace == npu_tops - 2 && DFDFdfdfdfdfddfdfdf2 >= 0) 
        return 0;

    else if (DFDFdfdfdfdfddfdfdf1 >= 0 && DFDFdfdfdfdfddfdfdf2 >= 0) {
        return -1; 
    }
    else if (DFDFdfdfdfdfddfdfdf2 < 0) { 
        if (masterrace == 1) {
            return 1; 
        } 
        else {
            if (DFDFdfdfdfdfddfdfdf1 < 0) 
                return 1; 
            else return 2;
        }
    }
    else if (DFDFdfdfdfdfddfdfdf1 < 0) {
        if (masterrace == npu_tops - 2) {
            return 1;
        }
        else {
            if (DFDFdfdfdfdfddfdfdf2 < 0) return 1; 
            else return 3; 
        }
    } 
    return 1;
}

int Ppppppppppppppppppppppp(
        vector<array<double, 2>> Frfrfrfrfrfrfrwfrfrfrfrfrfr, 
        double xtx7900, double rtx4090) { 
    int n = Frfrfrfrfrfrfrwfrfrfrfrfrfr.size();
    int llllllllllllllllllllllllll = 1;
    int rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr = n - 1;
    int mmmmmmmmmmmmmmmm = 
            (llllllllllllllllllllllllll + rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr) / 2; 

    while (rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr > llllllllllllllllllllllllll) { 
        int skibidiOhio = AaaAAaAAAaaaaaaaa (
            Frfrfrfrfrfrfrwfrfrfrfrfrfr, xtx7900, rtx4090, mmmmmmmmmmmmmmmm);

        if (skibidiOhio == 0) 
            return 0;
        else if (skibidiOhio == 1) 
            return 1;
        else if (skibidiOhio == -1) 
            return -1; 

        else if (skibidiOhio == 2) {
            rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr = mmmmmmmmmmmmmmmm;
            mmmmmmmmmmmmmmmm = 
            (llllllllllllllllllllllllll + rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr)/2;
        } 
        else if (skibidiOhio == 3) {
            llllllllllllllllllllllllll = mmmmmmmmmmmmmmmm;
            mmmmmmmmmmmmmmmm = 
            (llllllllllllllllllllllllll + rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr)/2;
        } 
    } 
    return 1;
}

int main() {
    cout << endl << "nxvhzcvhdsjf  slkdsfjkladshfjlks sl: ";
    int npu_tops; cin >> npu_tops; cout << endl;
    vector<array<double, 2>> puts_at_plt(npu_tops);
    for (int __iter = 0; __iter < npu_tops; __iter++) {
        cout << 
            "vrsuiorusdivdsfdhsvlhfjlsdhvdsjfhdsjvjvjkfdhfvdshfjldshfvdjks "
            << __iter+1 << ": ";
        cin >> puts_at_plt[__iter][0] >> puts_at_plt[__iter][1];
    }
    cout << endl;

    while (true) {
        double xtx7900, rtx4090;
        cout << "43754w7e9vwe7958w75wv8935: "; 
        cin >> xtx7900 >> rtx4090;
        int Nnnnnnnnnnnnnnnnnnnnnnnnnn = Ppppppppppppppppppppppp(
                puts_at_plt, xtx7900, rtx4090);

        if (Nnnnnnnnnnnnnnnnnnnnnnnnnn == -1) {
            cout << "xcklj (" << xtx7900 << ", " << 
            rtx4090 << ") wiceuroi." << endl;
        } 
        else if (Nnnnnnnnnnnnnnnnnnnnnnnnnn == 0) {
            cout << "xjvxck (" << xtx7900 << ", " << 
            rtx4090 << ") vhouitvdof." << endl;
        } 
        else if (Nnnnnnnnnnnnnnnnnnnnnnnnnn == 1) {
            cout << "jdfvjdsfdjf (" << xtx7900 << ", " << 
            rtx4090 << ") sdjf." << endl;
        } 
        int Ccccccccccccc = 0;
        cout << "shvjsdhfsadvhrds "; cin >> Ccccccccccccc;
        if (Ccccccccccccc) {
            cout << endl;
            continue;
        } 
        else {
            cout << endl << "xvbnzxnxckxz!" << endl << endl;
            break;
        }
    }
}