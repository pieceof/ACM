package hunnu10092;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Scanner input = new Scanner(System.in);
		int SIZE = 200;
		BigInteger []factorial = new BigInteger[SIZE]; 
		factorial[0] = BigInteger.ONE;
		for(int i=1;i<SIZE;++i)
		    factorial[i] = factorial[i-1].multiply( BigInteger.valueOf(i) );
		int n;
		BigInteger hex = BigInteger.valueOf(16);
		BigInteger x;
		BigInteger zero = BigInteger.ZERO;
		while ( input.hasNextInt() ){
			
			n = input.nextInt();
			if ( n < 0){
				break;
			}
			int ans = 0;
			x = factorial[n];
			while ( !x.equals(zero) ){
				if( x.mod( hex ).equals(zero)  )ans++;
				x = x.divide(hex);
			}
			System.out.println(ans);
		}
		input.close();

	}

}
