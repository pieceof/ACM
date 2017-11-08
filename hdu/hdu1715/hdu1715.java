package hdu;

import java.math.BigInteger;
import java.util.Scanner;

public class hdu1715 {
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		BigInteger []fib = new BigInteger[1010];
		fib[1] = fib[2] = BigInteger.ONE;
		for ( int i = 3;i <= 1000;++i ) {
			fib[i] = fib[i-1].add(fib[i-2]);
		}
		int n = cin.nextInt();
		for ( int i = 1;i <= n;++i ) {
			int x = cin.nextInt();
			System.out.println(fib[x]);
		}
		cin.close();
	}
}
