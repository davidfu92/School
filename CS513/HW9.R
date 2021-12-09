#' Company : Stevens
#' Project : HW9
#' Purpose : HW9
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : December 6, 2021
#' 
#' 
#' ###### Homework 9 ####
#' 
rm(list=ls())
set.seed(513)
#'
#'
#' Data pre-processing
#'
cancerData=read.csv("/Users/davidfu/Downloads/wisc_bc_ContinuousVar.csv", header=TRUE)

cancerData <- na.omit(cancerData)
cancerData$diagnosis <- as.factor(cancerData$diagnosis)
cancerData$diagnosis <- as.numeric(cancerData$diagnosis)
# create test and training dataset
index <- seq (1,nrow(cancerData),by=5)
test<-cancerData[index,]
training<-cancerData[-index,]
library('e1071')


svm.model <- svm( diagnosis~ ., data =training  )
svm.pred <- predict(svm.model,  test )

table(actual=test[,5],svm.pred )
SVM_wrong<- (test$diagnosis!=svm.pred)
rate<-sum(SVM_wrong)/length(SVM_wrong)

rate
#' Memory Clean up
rm(list=ls())

