
public class QuickSort {
	
	public void quickSort(int [] a, int start, int end) {
		
		if(start <= end) {
			int p = partition(a, start, end);
			quickSort(a, start, p - 1);
			quickSort(a, p + 1, end);
		}
		
	}
	
	private int partition(int [] a, int start, int end) {
		int pivPos = start + (end-start) / 2;
		
		
		for(int i = start; i < pivPos; i++) { // left half of array
			if(a[i] > a[pivPos]) { // swap
				if(i != pivPos - 1) {
					a[pivPos-1]+=a[i];
					a[i] = a[pivPos-1] - a[i];
					a[pivPos-1] = a[pivPos-1] - a[i];
				}
				
				
				a[pivPos-1]+=a[pivPos];
				a[pivPos] = a[pivPos-1] - a[pivPos];
				a[pivPos-1] = a[pivPos-1] - a[pivPos];
				
				pivPos--;
				i--;
			}  
		} 
		
		for(int i = pivPos + 1; i <= end; i++) { // right half of array
			if(a[i] < a[pivPos]) { // swap
				if(i != pivPos + 1) { 
					a[pivPos+1]+=a[i];
					a[i] = a[pivPos+1] - a[i];
					a[pivPos+1] = a[pivPos+1] - a[i];
				}
				
				
				a[pivPos]+=a[pivPos+1];
				a[pivPos+1] = a[pivPos] - a[pivPos+1];
				a[pivPos] = a[pivPos] -a[pivPos+1];
				
				pivPos++;
			}
		} 
		
		return pivPos;
	}

}
