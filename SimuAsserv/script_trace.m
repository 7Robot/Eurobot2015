clear all;

data_v=importdata('data_v.txt')
data_vt=importdata('data_vt.txt')
x = [1:size(data_v)]
figure

subplot(2,1,1)
plot(x,data_v(:,1),x,data_v(:,2),'r')

subplot(2,1,2)
plot(x,data_vt(:,1),x,data_vt(:,2),'r')
