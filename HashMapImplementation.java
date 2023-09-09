import java.util.ArrayList;
import java.util.List;
// package CustomCollectionImplementation

class HashMapLinkedList<K,V>{
    private List<MapNode<K,V>> bucket;
    private int capacity,size;
    private final int INITIAL_CAPACITY = 5;

    public HashMapLinkedList(){
        capacity=INITIAL_CAPACITY;
        bucket = new ArrayList</*MapNode<K,V>*/>();
        for(int i=0;i<capacity;i++){
            bucket.add(null);
        }
    }
    /*Value retrieval using Key*/
    public V get(K Key){
        int bucketIndex = getBucketIndex(Key);
        MapNode<K,V> head = bucket.get(bucketIndex);
        while(head!=null){
            if(head.key.equals(Key)){
                return head.value;
            }
            head=head.next;
        }
        return null;
    }
    
    /*updating for existing Key/adding*/
    public void put(K Key,V Value){
        int bucketIndex=getBucketIndex(Key);
        MapNode<K,V> head=bucket.get(bucketIndex);
        while(head!=null){
            if(head.key.equals(Key)){
                head.value=Value;
                return;
            }
            head = head.next;
        }
        size++;
        MapNode<K,V> newEntry = new MapNode<K,V>(Key,Value);
        head = bucket.get(getBucketIndex(Key));
        newEntry.next=head;
        bucket.set(bucketIndex,newEntry);


        double loadFactor = (1.0 * size)/capacity;
        if(loadFactor > 0.7)
            rehash();

    }
    public void rehash(){
        List<MapNode<K,V>>temp=bucket;
        bucket= new ArrayList</*MapNode<K,V>*/>();
        for(int i=0;i<2*capacity;i++){
            bucket.add(null);
        }
        capacity*=2;
        size=0;
        for(int i=0;i<temp.size();i++){
             MapNode<K,V> head = temp.get(i);
             while(head!=null){
                put(head.key,head.value);
                head=head.next;
             }   
        }
        return;
    }
    public int getBucketIndex(K key){
        int hashedIndex = key.hashCode();
        return hashedIndex % capacity;
    }
    public int getSize() { return size;}
    public int getCapacity() { return capacity;}

    /*removal of  Entry using Key*/
    public void remove(K Key){
        int bucketIndex = getBucketIndex(Key);
        MapNode<K,V> head = bucket.get(bucketIndex);
        MapNode<K,V> prev=null;
        while(head!=null){
            if(head.key.equals(Key)){
                if(prev==null)
                    bucket.set(bucketIndex,head.next);
                else 
                  prev.next=head.next;
                head.next=null;  
                size--;
                break;
            }
            prev=head;
            head=head.next;
        }
        return;
    }

    public class MapNode<K,V>{
        public K key;
        public V value;
        public MapNode<K,V> next;
        public MapNode(K key,V value)
        {
            this.key = key;
            this.value = value;
        }
    }
}

public class HashMapImplementation
{
    public static void main(String [] args)
    {
        /*Driver Code*/
        HashMapLinkedList<Integer,String> nameToLen=new HashMapLinkedList<Integer,String>();

        nameToLen.put(1, "a");
		nameToLen.put(6, "riddhi");
		nameToLen.put(5, "absxd");
		nameToLen.put(3, "abc");
		nameToLen.put(5, "riddd");
        nameToLen.put(7, "last");
        //nameToLen.remove(3);   
        
        System.out.println();
		System.out.println(nameToLen.get(5)+" "+ nameToLen.getCapacity()+ " "+nameToLen.getSize());
		System.out.println(nameToLen.get(1)+" "+ nameToLen.getCapacity()+ " "+nameToLen.getSize());
		System.out.println(nameToLen.get(6)+" "+ nameToLen.getCapacity()+ " "+nameToLen.getSize());
		System.out.println(nameToLen.get(3)+" "+ nameToLen.getCapacity()+ " "+nameToLen.getSize());
		System.out.println(nameToLen.get(7)+" "+ nameToLen.getCapacity()+ " "+nameToLen.getSize());
        nameToLen.remove(7);
        System.out.println(nameToLen.get(7)+" "+ nameToLen.getCapacity()+ " "+nameToLen.getSize());
    }    
}