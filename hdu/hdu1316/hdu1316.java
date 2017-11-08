package hdu;

import java.math.BigInteger;
import java.util.Scanner;

public class hdu1316 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in);
		BigInteger a,b ,c, l ,r;
		while ( cin.hasNext() ) {
			l = cin.nextBigInteger();
			r = cin.nextBigInteger();
			if ( l.equals(BigInteger.ZERO) && r.equals(BigInteger.ZERO) ) {
				break;
			}
			a = BigInteger.ZERO;
			b = BigInteger.ONE;
			int cnt = 0;
			c = a.add(b);
			while ( c.compareTo(r) < 1 ) {
				c = a.add(b);
				if ( c.compareTo(l) >= 0 && c.compareTo(r) <= 0 ) {
					cnt ++; 
				}
				a = b;
				b = c;
			}
			System.out.println(cnt);
			
		}
		cin.close();
	}

}
