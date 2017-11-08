package hdu;

import java.math.BigInteger;
import java.util.Scanner;

public class hdu1042 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in);
		BigInteger ans;
		int n;
		while ( cin.hasNext() ) {
			n = cin.nextInt();
			ans = BigInteger.ONE;
			for ( int i = 1;i <= n;++i ){
				ans = ans.multiply(BigInteger.valueOf(i));
			}
			System.out.println(ans);
		}
		cin.close();
	}

}
