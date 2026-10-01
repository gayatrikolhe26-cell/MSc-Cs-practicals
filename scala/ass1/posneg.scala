import scala.io.StdIn
object posneg{
    def main(args:Array[String]):Unit={
        print("enter an integer")
        val n1 = StdIn.readInt()
        val result=if(n1>0)"positive"else if(n1<0)"negative"else"zero"
        println(s"The $n1 is $result")
    }
}