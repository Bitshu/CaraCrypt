#include "CaraCrypt.hpp"
 
void CaraCrypt::InitCara ( void ) {
    this->LFSR = { 0x13579bdf, 0x2468ace0, 0xfdb97531 };
    this->MASK = { 0x80000062, 0x40000020, 0x10000002 };
    this->ROTA = { 0x7fffffff, 0x3fffffff, 0xfffffff };
    this->ROTB = { 0x80000000, 0xc0000000, 0xf0000000 };
    this->RNDA = { 0x0, 0x0, 0x0, 0x0, 0x0 };
}
 
void CaraCrypt::TransformKey ( const std::string Key ) {
    std::string Seed = ( Key.empty ( ) ) ? "C+!+(¦\x10'\t¬\x18V" : Key;
 
    for ( auto i = 0; i < Seed.length ( ) && Seed.length ( ) < 12; i++ )
        Seed += Seed[i];
    Seed.erase ( 12 );
 
    for ( auto i = 0; i < 4; i++ ) {
        this->LFSR [ 0 ] = ( this->LFSR [ 0 ] <<= 8 ) | Seed [ i ];
        this->LFSR [ 1 ] = ( this->LFSR [ 1 ] <<= 8 ) | Seed [ i + 4 ];
        this->LFSR [ 2 ] = ( this->LFSR [ 2 ] <<= 8 ) | Seed [ i + 8 ];
    }
 
    if ( ! this->LFSR [ 0 ] ) this->LFSR [ 0 ] = 0x13579bdf;
    if ( ! this->LFSR [ 1 ] ) this->LFSR [ 1 ] = 0x2468ace0;
    if ( ! this->LFSR [ 2 ] ) this->LFSR [ 2 ] = 0xfdb97531;
}
 
void CaraCrypt::TransformChar ( BYTE& character ) {
    int a = this->LFSR [ 1 ] & 1;
    int b = this->LFSR [ 1 ] & 1;
    int c = this->LFSR [ 2 ] & 1;
 
    for ( auto i = 0; i < 2; i++ ) {
        if ( ( this->LFSR [ 0 ] & 1 ) != 0 ) {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] ^ this->MASK [ 0 ] ) >> 1 | this->ROTB [ 0 ];
 
            if ( ( this->LFSR [ 1 ] & 1 ) != 0 ) {
                this->LFSR [ 1 ] = this->ROTB [ 1 ] | ( this->LFSR [ 1 ] ^ this->MASK [ 1 ] ) >> 1;
                b = 1;
                a = 1;
            } else {
                this->LFSR [ 1 ] = this->ROTA [ 1 ] & ( this->LFSR [ 1 ] >> 1 );
                b = 0;
                a = 0;
            }
        } else {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] >> 1 ) & this->ROTA [ 0 ];
 
            if ( ( this->LFSR [ 2 ] & 1 ) != 0 ) {
                this->LFSR [ 2 ] = this->ROTB [ 2 ] | ( this->LFSR [ 2 ] ^ this->MASK [ 2 ] ) >> 1;
                c = 1;
            } else {
                this->LFSR [ 2 ] = this->ROTA [ 2 ] & ( this->LFSR [ 2 ] >> 1 );
                c = 0;
            }
        }
 
        this->RNDA [ 0 ] = ( this->RNDA [ 4 ] << 1 ) | c ^ b;
 
        if ( ( this->LFSR [ 0 ] & 1 ) != 0 ) {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] ^ this->MASK [ 0 ] ) >> 1 | this->ROTB [ 0 ];
 
            if ( ( this->LFSR [ 1 ] & 1 ) != 0 ) {
                this->LFSR [ 1 ] = this->ROTB [ 1 ] | ( this->LFSR [ 1 ] ^ this->MASK [ 1 ] ) >> 1;
                a = 1;
            } else {
                this->LFSR [ 1 ] = this->ROTA [ 1 ] & ( this->LFSR [ 1 ] >> 1 );
                a = 0;
            }
        } else {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] >> 1 ) & this->ROTA [ 0 ];
 
            if ( ( this->LFSR [ 2 ] & 1 ) != 0 ) {
                this->LFSR [ 2 ] = this->ROTB [ 2 ] | ( this->LFSR [ 2 ] ^ this->MASK [ 2 ] ) >> 1;
                c = 1;
            } else {
                this->LFSR [ 2 ] = this->ROTA [ 2 ] & ( this->LFSR [ 2 ] >> 1 );
                c = 0;
            }
        }
 
        this->RNDA [ 1 ] = ( this->RNDA [ 0 ] << 1 ) | c ^ a;
 
        if ( ( this->LFSR [ 0 ] & 1 ) != 0 ) {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] ^ this->MASK [ 0 ] ) >> 1 | this->ROTB [ 0 ];
 
            if ( ( this->LFSR [ 1 ] & 1 ) != 0 ) {
                this->LFSR [ 1 ] = this->ROTB [ 1 ] | ( this->LFSR [ 1 ] ^ this->MASK [ 1 ] ) >> 1;
                a = 1;
            } else {
                this->LFSR [ 1 ] = this->ROTA [ 1 ] & ( this->LFSR [ 1 ] >> 1 );
                a = 0;
            }
        } else {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] >> 1 ) & this->ROTA [ 0 ];
 
            if ( ( this->LFSR [ 2 ] & 1 ) != 0 ) {
                this->LFSR [ 2 ] = this->ROTB [ 2 ] | ( this->LFSR [ 2 ] ^ this->MASK [ 2 ] ) >> 1;
                c = 1;
            } else {
                this->LFSR [ 2 ] = this->ROTA [ 2 ] & ( this->LFSR [ 2 ] >> 1 );
                c = 0;
            }
        }
 
        this->RNDA [ 2 ] = ( this->RNDA [ 1 ] << 1 ) | c ^ a;
 
        if ( ( this->LFSR [ 0 ] & 1 ) != 0 ) {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] ^ this->MASK [ 0 ] ) >> 1 | this->ROTB [ 0 ];
 
            if ( ( this->LFSR [ 1 ] & 1 ) != 0 ) {
                this->LFSR [ 1 ] = this->ROTB [ 1 ] | ( this->LFSR [ 1 ] ^ this->MASK [ 1 ] ) >> 1;
                a = 1;
            } else {
                this->LFSR [ 1 ] = this->ROTA [ 1 ] & ( this->LFSR [ 1 ] >> 1 );
                a = 0;
            }
        } else {
            this->LFSR [ 0 ] = ( this->LFSR [ 0 ] >> 1 ) & this->ROTA [ 0 ];
 
            if ( ( this->LFSR [ 2 ] & 1 ) != 0 ) {
                this->LFSR [ 2 ] = this->ROTB [ 2 ] | ( this->LFSR [ 2 ] ^ this->MASK [ 2 ] ) >> 1;
                c = 1;
            } else {
                this->LFSR [ 2 ] = this->ROTA [ 2 ] & ( this->LFSR [ 2 ] >> 1 );
                c = 0;
            }
        }
 
        this->RNDA [ 3 ] = ( this->RNDA [ 2 ] << 1 ) | c ^ a;
        this->RNDA [ 4 ] = this->RNDA [ 3 ];
        b = a;
    }
 
    character ^= this->RNDA [ 3 ];
 
    if ( this->RNDA [ 3 ] == character )
        character = this->RNDA [ 3 ];
}
 
void CaraCrypt::TransformBytes ( std::vector<BYTE>& Source, const std::string Key ) {
    this->InitCara ( ) ;
    this->TransformKey ( Key );
 
    for ( auto& character : Source )
        this->TransformChar ( character ) ;
}