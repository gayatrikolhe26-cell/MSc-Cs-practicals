object max2{
 def main(args:Array[String]):Unit={
        var a:Array[Int]= Array(10,0,30,40)
         var max1=0
         var max2=0
         if(a(0)>a(1)){
         max1=a(0)
         max2=a(1)}
         else{
         max1=a(1)
         max2=a(0)
         }
         if(a(2)>max1){
         max2=max1
         max1=a(2)
         }
         else if(a(2)>max2){
         max2=a(2)
         }
         if(a(3)>max1){
         max2=max1
         max1=a(3)
         }else if(a(3)>max2){
         max2=a(3)
         }
         println(s"the second maximum number is : $max2")
         }
}

