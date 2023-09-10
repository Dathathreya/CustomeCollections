import java.util.List;
import java.util.ArrayList;
import java.lang.*;
import java.io.*; import java.util.*;

class queueNode<T extends Comparable<T>> implements Comparable<queueNode<T>>
{
    private T node;
    private int cost;
    public queueNode(T node,int cost){
        this.node= node;
        this.cost = cost;
    }
    public T getNode(){
        return this.node;
    }
    public int getCost(){
        return this.cost;
    }
    @Override 
    public int compareTo(queueNode<T> qnode){
        return this.getNode().compareTo(qnode.node);
    }
}

class priorityQueue<T extends Comparable<T>>
{
   private List<queueNode<T>> minheap;
   private boolean isempty;
   private int size;
   public priorityQueue(){
        this.minheap = new ArrayList<queueNode<T>>();
        this.isempty=this.minheap.isEmpty(); 
        this.size = this.minheap.size();
   }
   public boolean isEmpty() {this.isempty=minheap.isEmpty();return this.isempty;}
   public int size() {this.size=minheap.size();return this.size;}
   
   // upheap, heapify
   public queueNode<T> peek() { if(this.isEmpty()){return null;} return this.minheap.get(0);}
   public queueNode<T> top(){ return this.peek(); }
   public void add(queueNode<T> newnode){
        this.minheap.add(newnode);
        int N=this.size();
        for(int i=N/2+1;i>=0;i--)
        {
            heapify(i,N);
        }
   } 
   public void pop(){
       if(this.isEmpty()){ return; } 
       //queueNode<T> top=this.peek(); 
        queueNode<T> last = this.minheap.get(size()-1);
        this.minheap.set(0,last);
        this.minheap.remove(size()-1);
        heapify(0,size());// top to bottom
   }
   private void heapify(int root,int n){
        int largest=root,left=2*root+1,right=2*root+2;
        if(left<n && (this.minheap.get(root).compareTo(this.minheap.get(left)))<0)
        {
            largest=left;
        }
        if(right<n && (this.minheap.get(root).compareTo(this.minheap.get(right)))<0)
        {
            largest=right;
        }
        if(largest!=root){
            queueNode<T> nd= this.minheap.get(largest);
            this.minheap.set(largest,this.minheap.get(root));
            this.minheap.set(root,nd);
            heapify(largest,n);
        }
   } 
}

public class MinHeap {
    public static void main(String[] args){
       // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int a=123,b=45;
        System.out.println(Integer.valueOf(a).compareTo(Integer.valueOf(b)));
        // List<queueNode<String>> lst= new ArrayList<>();
        // lst.add(new queueNode<String>("dcba",1));
        // lst.add(new queueNode<String>("cba",2));
        // lst.add(new queueNode<String>("ba",3));
        // lst.add(new queueNode<String>("ba",4));
        // Collections.sort(lst);
        // for(queueNode c: lst){
        //     System.out.println(c.getNode()+" "+c.getCost());
        // }
    }
}