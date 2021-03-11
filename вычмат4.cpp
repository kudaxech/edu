#include <iostream>
#include <vector>
#include <map>
#include <math.h> 

double f1 (double x)
{
    return 1 + cos(2*3.141592653589793*x) ;
}
double f2 (double x)
{
    return pow(2.718281828459045 , cos(2*3.141592653589793*x));
}
double k (double x)
{
    return 1;
}

double q ( double x)
{
    return pow(2.718281828459045 , sin(2*3.141592653589793*x));
}

double F ( double x,double k , double q)
{
    return  1/q + 1/(4*3.141592653589793*3.141592653589793*k + q )  * cos(3.141592653589793*2*x) ;
}

double rec (double h , int l , std::vector<double> A , std::vector<double> B , std::vector<double> &a , std::map < double , std::map <double , double> > M )
{
    if( l < 1/h )
    {
        a[l] = A[l] * rec(h,l+1,A,B,a,M) + B[l]; 
    }
    else
    {
        a[l] = ( M[l][3] - M[l][2]*B[l-1] )/( M[l][1] + M[l][2]*A[l-1] );
    }
    
    return a[l];
}

int main()
{
    double H = 0;
    const double step = 0.1;

    { 
        double max = 0 ;
        double h = 0.1;
        
        double  k = 1,
                q = 1;

        std::vector<std::vector<double> > accuracy;
    
        std::vector < double> U;

        for(;;)
        {
            
            std::vector <double> x(1/h + 1);
            x[0] = 0;


            for( int i = 1 ; i <= 1/h ; ++i)
            {
                x[i] = x[i-1] + h;
            }
            

            std::map < double , std::map <double , double> > M1,M2;

            ////////////////////////////////////////////

            M1[0][0] = 0 , M1[0][1] = 1 , M1[0][2] = 0 , M1[0][3] = 0; 
            
            for ( int l = 1 ; l <= 1/h - 1 ; ++l)
            {
                M1[l][0] = k , M1[l][1] = - 2*k - q*h*h , M1[l][2] = k , M1[l][3] = -h*h*f1(x[l]); 
            }

            M1[1/h][0] = 0 , M1[1/h][1] = 1 , M1[1/h][2] = 0 , M1[1/h][3] = 0; 

            ////////////////////////////////////////////

            M2[0][0] = 0 , M2[0][1] = 1 , M2[0][2] = 0 , M2[0][3] = 1; 
            
            for ( int l = 1 ; l <= 1/h - 1 ; ++l)
            {
                M2[l][0] = k , M2[l][1] = - 2*k - q*h*h , M2[l][2] = k , M2[l][3] = 0; 
            }

            M2[1/h][0] = 0 , M2[1/h][1] = 1 , M2[1/h][2] = 0 , M2[1/h][3] = 1; 

            

            ////////////////////////////////////////////

            std::vector < double > A1(1/h),B1(1/h),A2(1/h),B2(1/h);

            A1[0] = - (M1[0][0]/M1[0][1]) , B1[0] = M1[0][3] / M1[0][1] ; 

            for ( int l = 1 ; l <= 1/h - 1 ; ++l)
            {
                A1[l] = - ( M1[l][0]/ ( M1[l][1] + M1[l][2] * A1[l-1]  ) );
            }

            for ( int l = 1 ; l <= 1/h - 1 ; ++l)
            {
                B1[l] =  ( M1[l][3] - M1[l][2] * B1[l-1] ) / ( M1[l][1] + M1[l][2] * A1[l-1] );
            }

            /////////////////////////////////////////////

            A2[0] = - (M2[0][0]/M2[0][1]) , B2[0] = M2[0][3] / M2[0][1] ; 

            for ( int l = 1 ; l <= 1/h - 1 ; ++l)
            {
                A2[l] = - ( M2[l][0]/ ( M2[l][1] + M2[l][2] * A2[l-1]  ) );
            }

            for ( int l = 1 ; l <= 1/h - 1 ; ++l)
            {
                B2[l] =  ( M2[l][3] - M2[l][2] * B2[l-1] ) / ( M2[l][1] + M2[l][2] * A2[l-1] );
            }
            
            ///////////////////////////////////////////////

            std::vector<double> a(1/h + 1),b(1/h + 1);

            a[0] = A1[0]* rec(h,1,A1,B1,a,M1) + B1[0];

            b[0] = A2[0]* rec(h,1,A2,B2,b,M2) + B2[0];

            //////////////////////////////////////////////
            
            double u0 = (k * ( a[1] + a[1/h - 1]  ) + f1(0)*h*h )/( 2*k + q*h*h - k*( b[1] + b[1/h - 1] ) );

            
           
            std::vector<double> long_way;
            std::vector<double> short_way;
            

            for(int l = 0 ; l <= 1/h ; l++)
            {
                long_way.push_back(a[l] + u0*b[l]);
                
            }   
            for(int l = 0 ; l <= 10 ; ++l)
            {
                short_way.push_back(long_way[1/h*0.1*l]);
            }
            
            max = 0 ;
            for( int l = 0 ; l <= 1/h ; l++ )
            {   
                if( max < abs( F(h*l ,k,q) - long_way[l] ) )
                {
                    max = abs( F(h*l ,k,q) - long_way[l] ) ;
                }
            }

            
            H = h;

            h /= 2;

            accuracy.push_back({max,H});

            if( max < 0.0001 )
            {   
                U = short_way;
                break;
            }

        }

        std::cout << " Аналитическое решение задачи  "<<" число узлов в сетке: "<< 1/H + 1 << std::endl<<std::endl;
        for(int l = 0 ; l <= 10 ; ++l)
        {
            std::cout << F(step*l,k,q) <<"(точка сетки:"<< 0.1*l <<" ) /////  ";
        }
        std::cout << std::endl<< std::endl;

        

        std::cout << "Численное решение задачи  " <<" число узлов в сетке: "<< 1/H + 1 << std::endl<<std::endl;
        for(int l = 0 ; l <= 10 ; ++l)
        {
            std::cout << U[l] <<"(точка сетки:"<< 0.1*l <<" ) ///// ";
        }
        std::cout << std::endl<< std::endl;



        std::cout << " Убывание погрешности " << std::endl;
        for(auto item: accuracy)
        {
            std::cout << " Погрешность "<< item[0] << " число узлов: "<< 1/item[1] + 1 << std::endl;
        }
    }
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    { 
        
        double h = H;
        
        std::vector <double> x(1/h + 1);
        x[0] = 0;


        for( int i = 1 ; i <= 1/h ; ++i)
        {
            x[i] = x[i-1] + h;
        }
        

        std::map < double , std::map <double , double> > M1,M2;

        ////////////////////////////////////////////

        M1[0][0] = 0 , M1[0][1] = 1 , M1[0][2] = 0 , M1[0][3] = 0; 
        
        for ( int l = 1 ; l <= 1/h - 1 ; ++l)
        {
            M1[l][0] = k( x[l]+h/2 ) , M1[l][1] = -( k(x[l]+h/2) + k(x[l] - h/2) + q(x[l])*h*h  ) , M1[l][2] = k(x[l] - h/2) , M1[l][3] = - f2(x[l])*h*h ; 
        }

        M1[1/h][0] = 0 , M1[1/h][1] = 1 , M1[1/h][2] = 0 , M1[1/h][3] = 0; 

        ////////////////////////////////////////////

        M2[0][0] = 0 , M2[0][1] = 1 , M2[0][2] = 0 , M2[0][3] = 1; 
        
        for ( int l = 1 ; l <= 1/h - 1 ; ++l)
        {
            M2[l][0] = k( x[l]+h/2 ) , M2[l][1] = -( k(x[l]+h/2) + k(x[l] - h/2) + q(x[l])*h*h  ) , M2[l][2] = k(x[l] - h/2) , M2[l][3] = 0 ; 
        }

        M2[1/h][0] = 0 , M2[1/h][1] = 1 , M2[1/h][2] = 0 , M2[1/h][3] = 1; 

        

        ////////////////////////////////////////////

        std::vector < double > A1(1/h),B1(1/h),A2(1/h),B2(1/h);

        A1[0] = - (M1[0][0]/M1[0][1]) , B1[0] = M1[0][3] / M1[0][1] ; 

        for ( int l = 1 ; l <= 1/h - 1 ; ++l)
        {
            A1[l] = - ( M1[l][0]/ ( M1[l][1] + M1[l][2] * A1[l-1]  ) );
        }

        for ( int l = 1 ; l <= 1/h - 1 ; ++l)
        {
            B1[l] =  ( M1[l][3] - M1[l][2] * B1[l-1] ) / ( M1[l][1] + M1[l][2] * A1[l-1] );
        }

        /////////////////////////////////////////////

        A2[0] = - (M2[0][0]/M2[0][1]) , B2[0] = M2[0][3] / M2[0][1] ; 

        for ( int l = 1 ; l <= 1/h - 1 ; ++l)
        {
            A2[l] = - ( M2[l][0]/ ( M2[l][1] + M2[l][2] * A2[l-1]  ) );
        }

        for ( int l = 1 ; l <= 1/h - 1 ; ++l)
        {
            B2[l] =  ( M2[l][3] - M2[l][2] * B2[l-1] ) / ( M2[l][1] + M2[l][2] * A2[l-1] );
        }
        
        ///////////////////////////////////////////////

        std::vector<double> a(1/h + 1),b(1/h + 1);

        a[0] = A1[0]* rec(h,1,A1,B1,a,M1) + B1[0];

        b[0] = A2[0]* rec(h,1,A2,B2,b,M2) + B2[0];

        //////////////////////////////////////////////
        
        double u0 = ( k(h/2) * a[1] + k(x[1/h] - h/2 ) * a[1/h - 1 ] + f2(x[0])*h*h  )/( k(h/2) + k(x[1/h] - h/2 ) + q(x[0])*h*h - k(h/2)*b[1] - k(x[1/h] - h/2 )*b[1/h - 1 ]  );

        std::vector <double> u(1/h + 1);
        std::vector <double> short_way;// проекция сеточной функции на 11 точек

        for(int l = 0 ; l <= 1/h ; l++)
        {
            u[l] = a[l] + u0*b[l];
        }
        for(int l = 0 ; l <= 10 ; ++l)
        {
            short_way.push_back(u[1/h*0.1*l]);
        }


        std::cout <<"///////////////////////////////////////"<<std::endl<<"///////////////////////////////////////// "<<std::endl<<std::endl;

    
        std::cout << "Численное решение задачи с переменными коэффициентами  " <<" число узлов в сетке: "<< 1/H + 1 << std::endl<<std::endl;
        for(int l = 0 ; l <= 10 ; ++l)
        {
            std::cout << short_way[l] <<"(точка сетки:"<< 0.1*l <<" ) ///// ";
        }
        std::cout << std::endl<< std::endl;
        
    }



    return 0;
}
