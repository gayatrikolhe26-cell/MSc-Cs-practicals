import scala.io.StdIn
object HelloWorld{
    def main(args:Array[String]):Unit={
        print("enter an integer")
        val n1 = StdIn.readInt()
        val result=if(n1%2==0)"Even"else"Odd"
        println(s"The $n1 is $result")
    }
}