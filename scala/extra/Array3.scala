import scala.io.StdIn

object Array3{

  def main(args: Array[String]): Unit = {
    print("Enter number of elements: ")
    val n = StdIn.readInt()
    val numbers = new Array[Int](n)
    println("Enter "+n+ " elements:")
    var c=0
    for (i <- 0 until n) {
      numbers(i) = StdIn.readInt()
    }
    if(numbers.isEmpty){
    println("0")}
    else if(n<=3){
    var ans=numbers.sum
    println("the sum when the numbers are less then 3 in an array:"+ans)
    }else if(n>3){
    var ans2=numbers.takeRight(3).sum
    println(" the sum of last 3 elements in the array"+ans2)
    }
   }
}
