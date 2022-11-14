%%Tem de Resposta de Referencia
tem_resp_ref = 50000; %us
arquivo = fopen('dados.txt');
v = fscanf(arquivo,'%f');
disp('Tempo Mínimo')
minimo = min(v)
disp('Tempo Médio ')
medio = mean(v)

%Grafico de Casos
subplot(2,1,1)
plot(1:length(v),v,1:length(v),tem_resp_ref.*ones(length(v),1))
axis([0 length(v) 0 tem_resp_ref*1.2])
xlabel('Casos de Teste','fontweight','bold','fontsize',16)
ylabel('Tempo de Resposta [us]','fontweight','bold','fontsize',16)

%Gráfico histograma
subplot(2,1,2)
[h,x]=hist(v,[min(v):100:max(v)]);
bar(x,h);
colormap lines
axis([(min(v)-0.1) (max(v)*1.1) 0 1.1*max(h)])
xlabel('Tempo de Resposta [us]','fontweight','bold','fontsize',16)
ylabel('Frequência','fontweight','bold','fontsize',16)
