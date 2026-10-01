import scala.io.StdIn
object secondmax{
    def main(args:Array[String]):Unit={
         print("Enter 1st num")
         val a=StdIn.readInt()
         print("Enter second num")
         val b=StdIn.readInt()
         print("Enter third num")
         val c=StdIn.readInt()
         print("Enter fourth num")
         val d=StdIn.readInt()
         var max1=0
         var max2=0
         if(a>b){
         max1=a
         max2=b}
         else{
         max1=b
         max2=a
         }
         if(c>max1){
         max2=max1
         max1=c
         }
         else if(c>max2){
         max2=c
         }
         if(d>max1){
         max2=max1
         max1=d
         }else if(d>max2){
         max2=d
         }
         println(s"the second maximum number is : $max2")
         }
         }
