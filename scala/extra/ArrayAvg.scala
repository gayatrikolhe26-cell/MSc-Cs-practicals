import scala.io.StdIn

object ArrayAvg{

  def main(args: Array[String]): Unit = {
    print("Enter number of elements: ")
    val n = StdIn.readInt()
    val numbers = new Array[Int](n)
    println("Enter "+n+ " elements:")
    var c=0
    for (i <- 0 until n) {
      numbers(i) = StdIn.readInt()
    }
    for(i<-numbers){
    c=c+i
    }
    val avg=c/n
    println("the avg is :"+avg)
    }
 }
