package Path;

import java.util.ArrayList;
import java.util.Stack;

public class PathFinder{
	
	// Test interface
	public static void main(String []args){
		PathFinder pf = new PathFinder();
		ArrayList<PathMapProb> pmp = pf.findPath(123, 327);
		for(int i = 0; i < pmp.size(); i++){
			PathMapProb p = pmp.get(i);
			ArrayList<Integer> pa = p.path;
			for(int j = 0; j < pa.size(); j++){
				System.out.print(pa.get(j) + " ");
			}
			System.out.println();
			System.out.println(p.probability);
		}
	}
	
	// Parameters for find a good path
	private double alpha = 1.2;
	private double beta = 1.0;
	private double H = 0.5;
	private double theta = 1.0;
	
	// SubwayGraph
	private SubwayGraph sg;
	
	public PathFinder(){
		sg = new SubwayGraph();
	}
	
	public ArrayList<PathMapProb> findPath(int orientation, int destination){
		// Possible pathes
		ArrayList<Stack<Integer>> possiblePathes = new ArrayList<Stack<Integer>>();
		
		// Start position and finish position
		int start = SubwayGraph.id2Node(orientation);
		int finish = SubwayGraph.id2Node(destination);
		
		// Status storing
		int [] vertexStatus = new int[sg.getNumStations()];
		int [][] arcStatus = new int[sg.getNumStations()][sg.getNumStations()];
		
		// Route Searching
		Stack<Integer> stack = new Stack<Integer>();
		vertexStatus[start] = 1;
		stack.push(new Integer(start));
		while(!stack.isEmpty()){
			int elem = stack.peek();
			if(elem == finish){
				@SuppressWarnings("unchecked")
				Stack<Integer> s_temp = (Stack<Integer>) stack.clone();
				possiblePathes.add(s_temp);
				vertexStatus[elem] = 0;
				for(int row = 0; row < sg.getNumStations(); row++){
					for(int col = 0; col < sg.getNumStations(); col++){
						if(!stack.contains(new Integer(row)) && !stack.contains(new Integer(col))){
							arcStatus[row][col] = 0;
						}
					}
				}
				stack.pop();
			}else{
				int iter = 0;
				for(iter = 0; iter < sg.getNumStations(); iter++){
					if((vertexStatus[iter] == 0) && (arcStatus[elem][iter] == 0) && (sg.getWeight(elem, iter) != 0)){
						vertexStatus[iter] = 1;
						arcStatus[elem][iter] = 1;
						stack.push(new Integer(iter));
						break;
					}
				}
				if(iter == sg.getNumStations()){
					vertexStatus[elem] = 0;
					for(int row = 0; row < sg.getNumStations(); row++){
						for(int col = 0; col < sg.getNumStations(); col++){
							if(!stack.contains(new Integer(row)) && !stack.contains(new Integer(col))){
								arcStatus[row][col] = 0;
							}
						}
					}
					stack.pop();
				}
			}
		}
		
		// Calculating probability
		ArrayList<Double> cost = new ArrayList<Double>();
		ArrayList<ArrayList<Integer>> temp_pathes = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < possiblePathes.size(); i++){
			Stack<Integer> path = possiblePathes.get(i);
			ArrayList<Integer> shortPath = new ArrayList<Integer>();
			shortPath.add(SubwayGraph.node2Id(path.get(0)));
			double temp_rt = 0;
			double temp_ri = 0;
			double temp_ex = 0;
			for(int j = 0; j < path.size()-1; j++){
				temp_rt += sg.getWeight(path.get(j), path.get(j+1));
				if(Math.abs(path.get(j)-path.get(j+1)) > 2 || (path.get(j)==49 && path.get(j+1)==50) || ((path.get(j) == 50) && (path.get(j+1) == 49))){
					temp_ex += 1;
					temp_ri += alpha * Math.pow(temp_ex, beta) * sg.getWeight(path.get(j), path.get(j+1));
					temp_rt -= sg.getWeight(path.get(j), path.get(j+1));
					shortPath.add(SubwayGraph.node2Id(path.get(j)));
					shortPath.add(SubwayGraph.node2Id(path.get(j+1)));
				}
			}
			shortPath.add(SubwayGraph.node2Id(path.get(path.size()-1)));
			temp_pathes.add(shortPath);
			cost.add(new Double(temp_ri + temp_rt));
		}
		double minCost = Double.MAX_VALUE;
		for(int i = 0; i < cost.size(); i++){
			if(minCost > cost.get(i)){
				minCost = cost.get(i);
			}
		}
		ArrayList<Integer> idx = new ArrayList<Integer>();
		for(int i = 0; i < cost.size(); i++){
			if(cost.get(i) < (1 + H) * minCost){
				idx.add(i);
			}
		}
		double temp_sum = 0;
		for(int i = 0; i < idx.size(); i++){
			temp_sum += Math.exp(-theta * cost.get(idx.get(i)));
		}
		ArrayList<PathMapProb> pmp = new ArrayList<PathMapProb>();
		for(int i = 0; i < idx.size(); i++){
			pmp.add(new PathMapProb(temp_pathes.get(idx.get(i)), Math.exp(-theta * cost.get(idx.get(i)))/temp_sum));
		}
		
		return pmp;
	}
}

class PathMapProb{
	public ArrayList<Integer> path;
	public double probability;
	
	public PathMapProb(ArrayList<Integer> p, double prob){
		path = p;
		probability = prob;
	}
}
