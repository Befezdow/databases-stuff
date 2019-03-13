package study.JRM.support;

import java.util.Scanner;

public class JRMSupport {

	public static int readMenuChoice(Scanner in, int top, String label) {
		
		int index;
		while (true) {
			System.out.println("0 - go back");
			System.out.print(label);
			try {
				index = Integer.parseInt(in.nextLine());
			} catch (Throwable t) {
				System.out.println("Incorrect input");
				continue;
			}
			if (index == 0) {
				return -1;
			}
			index--;
			if (index < 0 || index >= top) {
				System.out.print("Incorrect index\n");
			} else {
				return index;
			}
		}
	}
}
