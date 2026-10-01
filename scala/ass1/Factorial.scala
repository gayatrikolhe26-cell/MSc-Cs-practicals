import scala.io.StdIn

object Factorial{
   def main(args: Array[String]): Unit = {
    println("enter an integer")
    val n=StdIn.readInt()
    var i=1
    var fact=1
    while(i<=n){
      fact=fact*i
      i=i+1
    }
    println("the factorial is "+ fact)
  }
}
