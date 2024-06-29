2. $Bit\ Rate = Baud\ Rate\times(log_2V)$，
   每毫秒采样 1 次，即每秒采样 1000 次，Baud Rate 为 1000 波特，
   若每次采样产生 16 位数据，则 maximum data rate 为 16 kbps
   若每次采样产生 1024位数据，则 maximum data rate 为 1.024 Mbps.

3. 根据 Shannel's theorem: $SNR=100$
   $C=B\times \log_2(1+SNR)\approx19.97kbps$,即 theoretical highest data rate 为 19.97 kbps
   根据奈奎斯特公式：$maximum\ data\ rate=2\times B\times \log_2V=6kbps$
   因此，the maximum achievable data rate is 6 kbps

4. 根据 Shannel's theorem: 
   $C=bandwidth\times \log_2(1+S/N)=100k\times\log_2(1+S/N)=1.544\times10^6$
   解得 $S/N=2^{15.44}-1\approx46dB$
   即使用大小为 46 dB 的信噪比

7. $bandwidth=1920\times1200\times24\times50=2.765Gbps$

8. Nyquist theorem指：如果一个函数的傅里叶频谱不包含频率在 $f$ 之上的正弦和余弦分量，以频率 $2f$ 对该函数采样，就可以获得全部信息。  
   在实际应用中，奈奎斯特用于计算在模拟信道上承载数字数据的最大数据率。因此，奈奎斯特定理适用于任何传输媒体，包括 high-quality single-mode optical fiber

21. 数据点相位一直是 0，使用了不同的振幅，因此是振幅调制 amplitude modulation

24. ADSL 有 256 个 channel：
    + Channel 0 for POTS
    + 1–5 not used
    + 250 channels
      - Upstream control (1)
      - Downstream control (1)
      - User data (248)
    每个 channel 为 4000 baud
    则 $Capacity\ of\ the\ downstream\ link=248\times\frac{3}{4}\times4000\times\log_2{64}=4.464Mbps$.

25. 10 个信道复用在一起需要 9 个 guard bands，
    则 $the\ minimum\ bandwidth=4000\times10+400\times9=43600Hz$

4-14. 