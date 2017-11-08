package hdu;

import java.math.BigInteger;
import java.util.Scanner;

public class hdu1002 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		BigInteger a , b ;
		int kase = 1;

		while ( t-- > 0 ) {
			
			a = cin.nextBigInteger();
			b = cin.nextBigInteger();
			System.out.printf("Case %d:\n\r",kase++);
//			System.out.println();
			System.out.println(a + " + " + b + " = " + a.add(b));
//			System.out.println(t);
			if ( t > 0 )System.out.println("");
		}
		
		cin.close();
	}

}
