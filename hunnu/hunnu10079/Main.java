package hunnu10079;


import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Scanner input = new Scanner(System.in);
		int SIZE = 105;
		BigInteger [][]C = new BigInteger[SIZE][SIZE]; 
		for(int i=0;i<SIZE;++i)for(int j=0;j<=i;++j){    
		    if ( 0 == j || i == j ) C[i][j] = BigInteger.ONE;    
		    else                    C[i][j] = C[i-1][j-1].add(C[i-1][j]) ;    
	    }    
		C[0][0] = BigInteger.ONE;//此处看情况
		int n,m;
		while ( input.hasNextInt()){
			
			n = input.nextInt();
			m = input.nextInt();
			if ( m == 0 && n == 0 ) break;
			System.out.print(n);
			System.out.print( " things taken " );
			System.out.print(m);
			System.out.print( " at a time is " );
			System.out.print(C[n][m]);
			System.out.println( " exactly." );
		}
		input.close();

	}

}
