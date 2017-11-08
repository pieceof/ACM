package hunnu;

import java.util.Scanner;

public class hunnu10730 {
	static String []opstr = {"+","-","*","/","(",")"};
	static String []oper = { "PLUS","MINUS","MULTI","DIVID","LEFT","RIGHT"}; 
	
	private static void _outoper(char ch) {
		for ( int i = 0;i < 6;++i ) {
			if ( ch == opstr[i].charAt(0) )
				System.out.println(oper[i]);
		}
	}
	private static void _outnub( String nub) {
		int a = Integer.valueOf(nub);
		System.out.println(Integer.toHexString(a));
	}
	private static boolean _isnub( char ch ) {
		if ( ch >= '0' && ch <= '9' ) return true;
		return false;
	}
	public static void tran( String str ) {
		String nub = "";
		for ( int i = 0;i < str.length();++i ) {
			if ( _isnub(str.charAt(i)) ) {
				nub += str.charAt(i);
			}else {
				if (nub.length() != 0) _outnub(nub);
				nub = "";
				_outoper( str.charAt(i));
			}
			
		}
		if (nub.length() != 0) _outnub(nub);
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in);
		String str;
		while( cin.hasNext() ) {
			str = cin.nextLine();
			tran(str);
		}
		cin.close();
	}

}
