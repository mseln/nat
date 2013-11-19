/* 3 dimensional matrix class
 * with Gauss Elimination and Eigenvectors
 * Source: Magnus Selin
 */

#include <cmath>

class Matrix3d{
    friend std::ostream& operator<< ( std::ostream& os, Matrix3d fb );
private:
    double a[3][3];
public: 
    Matrix3d(){     
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(j >= 0 && j < 3 && i >= 0 && i < 3) a[i][j] = 0;
            }
        }
    }

    double get(int i, int j)            { if(j >= 0 && j < 3 && i >= 0 && i < 3) return a[i][j];    else std::cerr << "Out of bounds! \n"; }
    void set(int i, int j, int v)   { if(j >= 0 && j < 3 && i >= 0 && i < 3) a[i][j] = v;       else std::cerr << "Out of bounds! \n"; }; 
    
    void chg_row(int x, int y);
    void mult_row(int x, double c);
    void add_row(int x, int y, double c);
    
    Matrix3d gauss();
    Matrix3d get_inverse();
    
    double get_det();
    void get_eigenvectors();
    
    Matrix3d operator=  (Matrix3d);
    Matrix3d operator+  (Matrix3d);
    Matrix3d operator-  (Matrix3d);
    Matrix3d operator*  (Matrix3d);
    Matrix3d operator*  (double);
};

void Matrix3d::chg_row(int x, int y){
    int temp[3] = {a[x][0], a[x][1], a[x][2]};
    
    for(int i = 0; i < 3; i++){
        a[x][i] = a[y][i];
        a[y][i] = temp[i];
    }
    
}
void Matrix3d::mult_row(int x, double c){
    for(int i = 0; i < 3; i++){
        a[x][i] *= c;
    }
}
void Matrix3d::add_row(int x, int y, double c){
    for(int i = 0; i < 3; i++){
        a[x][i] += c * a[y][i];
    }
}

void Matrix3d::get_eigenvectors(){
    double eig[3];
    double p = a[0][1] * a[0][1] + a[0][2] * a[0][2] + a[1][2] * a[1][2];
    double q, r, phi;
    Matrix3d B; Matrix3d I;
    for (int i = 0; i < 3; i++) I.set(i, i, 1);
    
    if ( p == 0 ){
        eig[0] = a[0][0];
        eig[1] = a[1][1];
        eig[2] = a[2][2];
    }
    else {
        q = (a[0][0] + a[1][1] + a[2][2]) / 3;
        p = (a[0][0] - q) * (a[0][0] - q) + 
            (a[1][1] - q) * (a[1][1] - q) + 
            (a[2][2] - q) * (a[2][2] - q) + 2 * q;
        p = sqrt( p / 6 );
        
        B = ((*this) - I * q);
        B = B * (1 / p);
        r = B.get_det();
        
        if (r <= -1)
            phi = M_PI / 3;
        else if (r >= 1)
            phi = 0;
        else
            phi = acos(r) / 3;
        
        eig[0] = q + 2 * p * cos(phi);
        eig[2] = q + 2 * p * cos(phi + M_PI * (2/3));
        eig[1] = 3 * q - eig[0] - eig[2]; 
    }
    
    std::cout << eig[0] << ' ' << eig[1] << ' ' << eig[2] << ' ';
    
    for (int i = 0; i < 3; i++) {
        Matrix3d temp = (*this);
        
        temp.set(0, 0, temp.get(0, 0) - eig[i]);
        temp.set(1, 1, temp.get(1, 1) - eig[i]);
        temp.set(2, 2, temp.get(2, 2) - eig[i]);
        temp = temp.gauss();
        
        std::cout << "Temp " << i << ":\n" << temp << "\n";
    }
}

double Matrix3d::get_det(){
    return  a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1] - 
            a[0][2] * a[1][1] * a[2][0] - a[0][1] * a[1][0] * a[2][2] - a[0][0] * a[1][2] * a[2][1];
}


Matrix3d Matrix3d::gauss(){
    Matrix3d * temp = new Matrix3d;
    temp = this;
    
    for (int i = 0; i < 3; i++){
        if(temp->get(i, i) == 0){
            for (int j = i; j < 3; j++){
                if(temp->get(j, i) != 0){
                    temp->chg_row(i, j);
                    break;
                }
            }
            
            if(temp->get(i, i) == 0){ 
                std::cout << "Parameter solotion!!\n";
                break;
            }
        }
        
        
        double mult_val = temp->get(i, i);
        temp->mult_row(i, 1 / mult_val );

        for (int j = 0; j < 3; j++){
            if(i != j){
                double mult_val = -temp->get(j, i);
                temp->add_row(j, i, mult_val);
            }
        }
    }
    
    std::cout << "Temp " << ":\n" << *temp << "\n";
    std::cout << "This " << ":\n" << *this << "\n";
    
    return *temp;
}

Matrix3d Matrix3d::get_inverse(){
    Matrix3d temp = (*this) , inverse;
    for (int i = 0; i < 3; i++) inverse.set(i, i, 1);
    
    for (int i = 0; i < 3; i++){
        if(temp.get(i, i) == 0){
            for (int j = i; j < 3; j++){
                if(temp.get(j, i) != 0){
                    temp.chg_row(i, j);
                    inverse.chg_row(i, j);
                    
                    std::cout << "Change row " << i << " and " << j << ".\n";
                    std::cout << temp << '\n';
                    std::cout << inverse << '\n';
                    
                    break;
                }
            }
            
            if(temp.get(i, i) == 0){ 
                std::cout << "Singularity!\n";
                break;
            }
        }
        
        
        double mult_val = temp.get(i, i);
        temp.mult_row(i, 1 / mult_val );
        inverse.mult_row(i, 1 / mult_val );
        
        std::cout << "Divide row " << i << " by " << mult_val << ".\n";
        std::cout << temp << '\n';
        std::cout << inverse << '\n';
        
        for (int j = 0; j < 3; j++){
            if(i != j){
                
                double mult_val = -temp.get(j, i);
                
                temp.add_row(j, i, mult_val);
                inverse.add_row(j, i, mult_val);
                
                std::cout << "Multiply row " << i << " by " << mult_val << " and adding it to " << j << ".\n";
                std::cout << temp << '\n';
                std::cout << inverse << '\n';
            }
        }
    }
    
    return inverse;
}

Matrix3d Matrix3d::operator= (Matrix3d param){
    Matrix3d temp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp.set(i, j, param.get(i, j));
        }
    }
    
    return temp;
}
Matrix3d Matrix3d::operator+ (Matrix3d param){
    Matrix3d temp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp.set(i, j, a[i][j] + param.get(i, j));
        }
    }
    
    return temp;
}
Matrix3d Matrix3d::operator- (Matrix3d param){
    Matrix3d temp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp.set(i, j, a[i][j] - param.get(i, j));
        }
    }
    
    return temp;
}
Matrix3d Matrix3d::operator* (double param){
    Matrix3d temp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp.set(i, j, a[i][j] * param);
        }
    }
    
    return temp;
}
Matrix3d Matrix3d::operator* (Matrix3d param){
    Matrix3d temp;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp.set(i, j,  a[i][0] * param.get(0,j) + 
                            a[i][1] * param.get(1,j) + 
                            a[i][2] * param.get(2,j)  );
        }
    }
    
    return temp;
}

std::ostream& operator << ( std::ostream& os, Matrix3d m ){
    for(int i = 0; i < 3; i++){
        os << "(";
        for(int j = 0; j < 3; j++){
            os << m.get(i, j) << ",\t";
        }
        os << ") \n";
    }
    return os;
}