#include<iostream>
#include<cmath>
#include<vector>
#include<math.h>
#include<algorithm>
#include<map>

struct Polynom
{   
    Polynom(std::vector<long double> coef)
    {
        a0 = coef[0];
        a1 = coef[1];
        a2 = coef[2];
        a3 = coef[3];
        a4 = coef[4];
        a5 = coef[5];
        a6 = coef[6];
    }
    long double a0,a1,a2,a3,a4,a5,a6 = 0;

    int value_in_point( long double point)
    {
        if( a0*pow(point,6) + a1*pow(point,5) + a2*pow(point,4) + a3*pow(point,3) + a4*pow(point,2) + a5*point + a6 > 0 )
        {
            return 1;
        }
        else if( a0*pow(point,6) + a1*pow(point,5) + a2*pow(point,4) + a3*pow(point,3) + a4*pow(point,2) + a5*point + a6 < 0)
        {
            return -1;
        }
        else if( a0*pow(point,6) + a1*pow(point,5) + a2*pow(point,4) + a3*pow(point,3) + a4*pow(point,2) + a5*point + a6 == 0 )
        {
            return 0;
        }
    }


};

std::vector<long double> returnVertexOfSegmentsAfterCutting ( std::map<std::string , long double> segment_of_roots , double quantity_of_fragmentation)
{
    long double main_segment_len = segment_of_roots["right"] - segment_of_roots["left"];

    double n = quantity_of_fragmentation;

    long double left = segment_of_roots["left"];
    long double right = segment_of_roots["right"];

    std::vector<long double> vertex_of_segments;


    for ( double i = 0 ; i < n + 1 ; i++)
    {
        vertex_of_segments.push_back( left + main_segment_len*i/n );

    }

    return vertex_of_segments;
}

std::vector< std::vector<long double> > getSegmentsOfRoots(std::map <std::string , long double> segment_of_roots , int approximate_quantity_of_positive_roots , std::vector<long double> coef )
{       
    std::vector< std::vector<long double> > last_vector;


    std::vector<long double> vertex = returnVertexOfSegmentsAfterCutting(segment_of_roots, (long double)pow(10,5) );
    Polynom polynom = coef;


    long double left = segment_of_roots["left"];
    long double right = segment_of_roots["right"];
    int k = (long double)pow(10,5);
    int n = 0;


    while( n != approximate_quantity_of_positive_roots )
    {
        last_vector.clear();
        n = 0;
        
        for ( int i = 1 ; i < vertex.size() ; i++ )
        {
            if( polynom.value_in_point( vertex[i-1] ) * polynom.value_in_point( vertex[i] ) < 0  )
            {
                n++;
                last_vector.push_back( { vertex[i-1] , vertex[i] } );

            }
            else if( polynom.value_in_point( vertex[i-1] ) == 0 )
            {
                n++;
                last_vector.push_back( { vertex[i-1] , vertex[i-1] } );
            }

            
            // std::cout << " n = "<< n << std::endl;
            // std::cout << vertex[1]<< "   " << vertex[vertex.size()-2]<< " "<<vertex[vertex.size()-1]<<std::endl;
            // std::cout << " я проверил " << i << " элемент "<< std::endl;

            if(n == approximate_quantity_of_positive_roots)
            {
                break;
            }  
        }

        k *= 2;
        vertex = returnVertexOfSegmentsAfterCutting(segment_of_roots, k ); 
        
    }


    return last_vector;
}

int main()
{
    long double gamma0 = 5.0/3.0,
                gamma3 = 7.0/5.0,
                ro0 = 7.9,
                ro3 = 11.37,
                U0 = -2.72 * pow(10,4),
                U3 = 2.28 * pow(10,4),
                P0 = 3.04 * pow(10,9),
                P3 = 1.17928 * pow(10,9);

    long double C0 = sqrt( gamma0 * (P0/ro0) ),
                C3 = sqrt( gamma3 * (P3/ro3) );

    long double alpha0 = ( gamma0 + 1 )/( gamma0 - 1),
                alpha3 = ( gamma3 + 1 )/( gamma3 - 1);

    long double X = P3/P0;

    long double e0 = 2*pow(C0,2) / ( gamma0*(gamma0 - 1)*pow( U3 - U0 , 2 ) ),
                e3 = 2*pow(C3,2) / ( gamma3*(gamma3 - 1)*pow( U3 - U0 , 2 ) );


    long double a0 = pow( alpha0*e3 - alpha3*X*e0 , 2 ),

                a1 = 2 * ( ( alpha0*e3 - alpha3*X*e0 ) * ( e3*(1-2*alpha0*X) - e0*X*(X-2*alpha3) ) - alpha0*alpha3*X*(alpha0*e3+alpha3*X*e0) ),

                a2 = pow( e3 , 2 ) * ( 6*pow( alpha0 * X ,2) - 8*alpha0*X + 1 ) - 2*e0*e3*X*( alpha0*alpha3*( pow(X,2)+ 4*X + 1 ) - 2*(X+1)*(alpha3+alpha0*X) + X ) + pow(e0*X,2)*( 6*pow(alpha3,2) - 8*alpha3*X + pow(X,2) ) + pow(alpha0*alpha3*X,2) - 2*alpha0*X*e3*(alpha0*X - 2*alpha0*alpha3*X + 2*alpha3 ) - 2*alpha3*e0*pow(X,2)*(alpha3 + 2*alpha0*X - 2*alpha0*alpha3 ) ,

                a3 = (-2)*X*( 2*pow(e3,2)*( pow(alpha0*X,2) - 3*alpha0*X + 1) + e0*e3*( (alpha3 + alpha0*X)*( pow(X,2) + 4*X + 1 ) - 2*alpha0*alpha3*X*(X+1) - 2*X*(X+1) ) + 2*X*pow(e0,2)*( pow(X,2) - 3*alpha3*X + pow(alpha3,2) ) - alpha0*alpha3*X*( alpha0*X + alpha3 ) + e3*( pow(alpha0*X , 2)*alpha3 - 2*X*( 2*alpha0*alpha3 + pow(alpha0,2)*X ) +2*alpha0*X + alpha3 ) + e0*X*( alpha0*pow(alpha3,2) - 2*alpha3*(alpha3 + 2*alpha0*X) + 2* alpha3*X + alpha0*pow(X,2) ) ),

                a4 = pow(X,2)*( pow(e3,2)*( pow(alpha0*X,2) - 8*alpha0*X + 6 ) - 2*e0*e3*( alpha0*alpha3*X -2*(X+1)*(alpha3+alpha0*X) + pow(X,2) + 4*X + 1 ) + pow(e0,2)*( pow(alpha3,2) - 8*alpha3*X + 6*pow(X,2) ) + ( pow(alpha3,2) + 4*alpha0*alpha3*X + pow(alpha0*X,2) ) - 2*e3*( ( X*pow(alpha0,2) + 2*alpha0*alpha3)*X - 2*( 2*alpha0*X + alpha3) + 1 ) - 2*e0*( alpha3*( 2*alpha0*X + alpha3 ) - 2*X*(2*alpha3 + alpha0*X) + pow(X,2) ) ) ,

                a5 = 2*pow(X,3)*( pow(e3,2)*(alpha0*X - 2) - e0*e3*(alpha0*X - 2 + alpha3 - 2*X) + pow(e0,2)*(alpha3 - 2*X) + (alpha3 + alpha0*X) - e3*(2*alpha0*X + alpha3 - 2) - e0*(2*alpha3 + alpha0*X - 2*X) ),

                a6 = pow(X,4)*( pow(e3-e0,2) + 1 - 2*(e3+e0) );                                                                                                   

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    std::cout<< a0 << " " <<  a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << a6 << std::endl; 
    std::vector<long double> coef = { a0,a1,a2,a3,a4,a5,a6 };
    std::vector <long double> Av = { fabs(a1),fabs(a2),fabs(a3),fabs(a4),fabs(a5),fabs(a6) };
    std::vector <long double> Bv = { fabs(a0),fabs(a1),fabs(a2),fabs(a3),fabs(a4),fabs(a5) };

    long double A = *max_element(Av.begin(),Av.end());
    long double B = *max_element(Bv.begin(),Bv.end());

    //std::cout<< A <<" "<< B <<std::endl;

    std::map<std::string, long double> segment_of_roots;

    segment_of_roots["left"] =  fabs(a6)/(fabs(a6) + B);
    segment_of_roots["right"] = 1 + A/fabs(a0);

    //std::cout << segment_of_roots["left"]<<" "<<segment_of_roots["right"]<<std::endl;

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    int approximate_quantity_of_positive_roots = 0;

    long double first = a0;

    for( int i = 1 ; i < 7 ; i++ )
    {
        if(first*coef[i] < 0)
        {
            approximate_quantity_of_positive_roots++;

        }
        first = coef[i];
    }
    std::cout << approximate_quantity_of_positive_roots<<std::endl;

    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    std::vector < std::vector < long double > > last_vector = getSegmentsOfRoots(segment_of_roots,approximate_quantity_of_positive_roots,coef);

    for ( int i = 0 ; i < last_vector.size() ; i++ )
    {
        std::cout << last_vector[i][0] << " " << last_vector[i][1] << std::endl;

    }

    ////////////////////////////////////////////////////////////////////
    ///////////          OUTPUT SEGMENTS             ///////////////////
    ////////////////////////////////////////////////////////////////////

    long double accurate = 1;
    std::vector<long double> roots;

    std::cout << " Введите необходимую для посчета корней точность: ";
    std::cin >> accurate ;
    std::cout << std::endl;

    long double step = 2 * accurate;
    Polynom polynom = coef;

   

    for ( auto item : last_vector )
    {
        if( item[0] == item[1] )
        {
            std::cout << " Нуль: " << item[0] << " +- "<< accurate <<std::endl;
            roots.push_back( item[0] );
        }
        else
        {
        
           long double l = item[0];
          // std::cout << " item[0] = "<<item[0]<< std::endl;
           while ( l + step <= item[1] )
           {
               if(polynom.value_in_point(l) == 0 )
                {
                    std::cout << " Нуль: " << l <<" +- "<< accurate<<std::endl;
                    roots.push_back( l );
                }
                else if( polynom.value_in_point(l)*polynom.value_in_point(l+step) < 0 )
                {
                    long double root = ( l + l +step ) / 2.0 ; 
                    std::cout << " Нуль: " << root << " +- "<< accurate << std::endl;
                    roots.push_back( root );
                }

                l += step;
           }


        }
        

    }
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    for( auto item : roots )
    {   
        long double ro1 = ro0*( gamma0 - 1 +(gamma0 + 1)*item )/( gamma0 + 1 + (gamma0 - 1)*item );

        long double U11 = U0 + (item*P0 - P0)/( ro0*C0*pow( ( gamma0 - 1 +(gamma0 + 1)*item )/(2*gamma0) , 0.5  )  ),
                    U12 = U0 - (item*P0 - P0)/( ro0*C0*pow( ( gamma0 - 1 +(gamma0 + 1)*item )/(2*gamma0) , 0.5  )  ),
                    U1 = 0;


        if( U11 > 0)
        {
            U1 = U11;
        }
        else if( U12 > 0 )
        {
            U1 = U12;
        }


        if( U1 != 0 )
        {   
            long double D0 = ( ro1*U1-ro0*U0 )/(ro1 - ro0);
            long double D3 = (P3-item*P0)/(ro3*(U3-U1)) + U3;

            if( D0 >= 0 and D3 >= 0)
            {   
                std::cout << " D0 = "<< D0 <<std::endl;
                std::cout << " D3 = "<<D3<<std::endl;
            }
        }
    }
    
    return 0;
}
