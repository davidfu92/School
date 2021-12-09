#' Company : Stevens
#' Project : HW7
#' Purpose : HW7
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : November 15, 2021
#' 
#' 
#' ###### Homework 7 ####
#' 
rm(list=ls())
library("neuralnet")
set.seed(513)
#'
#'
#' Data pre-processing
#'
cancerData=read.csv("/Users/davidfu/Downloads/wisc_bc_ContinuousVar.csv", header=TRUE)


index<-sort(sample(nrow(cancerData),round(.30*nrow(cancerData))))
training<-cancerData[-index,]
test<-cancerData[index,]

net_Cancer<- neuralnet( diagnosis~.,training, hidden=5, threshold=0.01)

#Plot the neural network
plot(net_Cancer)

## test should have only the input colum
ann <-compute(net_Cancer , test[,-2])
ann$net.result 

ann_cat<-ifelse(ann$net.result <.5,1,2)
length(ann_cat)

wrong<- (test$diagnosis!=ann_cat)
error_rate<-sum(wrong)/length(wrong)
error_rate

#' Memory Clean up
rm(list=ls())

