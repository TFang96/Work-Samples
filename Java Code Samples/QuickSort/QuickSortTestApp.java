import java.util.LinkedHashMap;

public class QuickSortTestApp {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		int[] a = {3, 5, 4, 2, 10, 0, 6, -7, -2, 1, 88, 22, 3, 4, 6, 5};
		
		LinkedHashMap<Integer, Integer> originalArrayData = new LinkedHashMap<Integer, Integer> ();
		LinkedHashMap<Integer, Integer> sortedArrayData = new LinkedHashMap<Integer, Integer> ();
		
		for(int i = 0; i < a.length; i++) {
			if(originalArrayData.containsKey(a[i]))
				originalArrayData.put(a[i], originalArrayData.get(a[i]) + 1);
			else
				originalArrayData.put(a[i], 1);
		}
		
		QuickSort q = new QuickSort();
		
		System.out.println("Original Array: ");
		for(int i = 0; i < a.length; i++)
			System.out.print(a[i] + " ");
		System.out.println("");
		
		q.quickSort(a, 0, a.length-1);
		
		for(int i = 0; i < a.length; i++) {
			if(sortedArrayData.containsKey(a[i]))
				sortedArrayData.put(a[i], sortedArrayData.get(a[i]) + 1);
			else
				sortedArrayData.put(a[i], 1);
		}
		
		
		
		System.out.println("");
		
		System.out.println("Sorted array: ");
		for(int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
		if(!sameArrayData(originalArrayData, sortedArrayData))
			System.out.println("There is an issue with the sort... ");

	}
	
	public static boolean sameArrayData(LinkedHashMap<Integer, Integer>a, LinkedHashMap<Integer, Integer>b) {
		boolean same = true;
		for(Integer k : a.keySet()) {
			if(!b.containsKey(k))
				same = false;
			else {
				if(a.get(k) != b.get(k))
					same = false;
			}
		}
		return same;
	}

}
