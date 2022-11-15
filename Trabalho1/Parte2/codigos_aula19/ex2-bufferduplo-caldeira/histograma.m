%%Tem de Resposta de Referencia
tem_resp_ref = 50; %ms
arquivo = fopen('dados.txt');
v = fscanf(arquivo,'%f');
v=v./1000;%transforma dados em ms
subplot(2,1,1)
%bar(v)
plot(1:length(v),v,1:length(v),tem_resp_ref.*ones(length(v),1))
axis([0 length(v) 0 1.1*max(v)])
%axis([0 length(v) 0 200])
xlabel('Casos de Teste','fontweight','bold','fontsize',16)
ylabel('Tempo de Resposta [ms]','fontweight','bold','fontsize',16)

subplot(2,1,2)
[h,x]=hist(v,[min(v):0.5:max(v)]);
bar(x,h);
colormap lines
axis([(min(v)-0.1) 60 0 1.1*max(h)])
xlabel('Tempo de Resposta [ms]','fontweight','bold','fontsize',16)
ylabel('Frequência','fontweight','bold','fontsize',16)
