arquivo = fopen('dados_sensores.txt');
v = fscanf(arquivo,'%f\t%f\t%f\t%f\n',[4 inf]);
v=v';

plot(v(:,1),v(:,2),v(:,1),v(:,3))
legend('Temperatura','Altura');

xlabel('Tempo (s)','fontweight','bold','fontsize',16)
ylabel('Temperatura e Altura','fontweight','bold','fontsize',16)