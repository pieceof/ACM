package hysbz1213;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	static BigInteger one = BigInteger.ONE;
	static BigInteger two = BigInteger.valueOf(2);
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		int m = input.nextInt();
		BigInteger n = input.nextBigInteger();
		
		BigInteger l = BigInteger.ZERO;
		BigInteger r = one;
		while ( r.pow(m).compareTo(n) < 1){
			l = r;
			r = r.multiply(two);
		}
		BigInteger mid;
		while ( l.compareTo(r) == -1 ){
			mid = l.add(r).divide(two);
			if ( mid.pow(m).compareTo(n) <= 0 ) l = mid.add(one);
			else r = mid;
		}
		System.out.println(l.subtract(one));
				
		input.close();
	}

}
