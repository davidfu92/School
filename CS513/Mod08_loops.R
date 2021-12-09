
#################################################
#  Company    : Stevens 
#  Project    : R Bootcamp 
#  Purpose    : Vectorization
#  First Name  : Khasha
#  Last Name  : Dehnad
#  Id			    : 12345
#  Date       :
#  Comments   :

#################################################
##   Step:
## 
##    for
##    while
##    repeat
##    next
##    break
##
##
##
##
##
##
######################
rm(list=ls())
x <- c("a", "b", "c", "d")
for(i in 1:4){
  print(x[i])
}

j<-0
for(i in x){
  j<-j+1
  print(x[j])
}

for(i in x){  
  print(i)
}

count<-0
while(count < 10) {
   print(count)
   count <- count + 1
 
   }


for(i in 1:100) {
  if(i <= 20|i ==28 ) {
    ## Skip the first 20 iterations and the 28th
    next
  }
  ## Skip after the 50th
  if(i >= 50) {
     
    break
  }
  print(i)
}

logical1<-c(F,T,T,F,F,F)
logical2<-c(F,F,T,T,F,F)

logical1 &  logical2
logical1 && logical2

logical1 |  logical2
logical1 || logical2

     
 