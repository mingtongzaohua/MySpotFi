function [PhsSlope, PhsCons] = removePhsSlope(vna_response,M,SubCarrInd,N)%#codegen
useCvxgen = 0;
if ~useCvxgen
    PhsRelFirstPac = unwrap(angle(vna_response));
    % angle提取相位角,复数数组vna_response 的每个元素返回相位角（以弧度为单位）。此角度介于 ±π 之间。
    % unwrap 解卷绕，使相位在pi处不发生跳变，从而反应出真实的相位变化,通过在向量 P 中增加 ±2π 的倍数来更正弧度相位角
    % % Below code is for when you are using phase relative to
    % % the first packet.
    for antIdForPhs = 1:M
        if  PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) > pi
            PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) - 2*pi;
            % 满足条件后此列所有元素都进行了这样的处理
        elseif PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) < -pi
            PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) + 2*pi;
        end
    end
    A = [repmat(SubCarrInd(:), M, 1) ones(N*M, 1)];
    x = A\PhsRelFirstPac(:);
    %则相当于inv（A）*B，意思就是A左除B,相当于A的逆矩阵左乘B。
    %x = A\B 是方程 Ax = B 的解。矩阵 A 和 B 必须拥有相同的行数。
    %PhsRelFirstPac(:)
    %按照列展开为90*1，1234-1324
    PhsSlope = x(1);
    PhsCons = x(2);%x为2阶矩阵
    
%     sprintf('estimation error is %f', norm(PhsRelFirstPac(:) - A*x)/length(PhsRelFirstPac(:)))
%     figure(100); plot(PhsRelFirstPac(:) - A*x); hold on;
    
%     % % % % % % % % Removing exact slope
%             cvx_begin quiet
%                 variable PhsSlope
%                 variable PhsCons
%         %         PhsRelFirstPac = exp(1i*angle(csi_plot))./phaseFirstPac;
%                 PhsRelFirstPac = unwrap(angle(vna_response));
%                 % % Below code is for when you are using phase relative to
%                 % % the first packet.
%                 for antIdForPhs = 1:M
%                     if  PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) > pi
%                         PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) - 2*pi;
%                     elseif PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) < -pi
%                         PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) + 2*pi;
%                     end
%                 end
%                 minimize( norm( PhsRelFirstPac - PhsSlope*repmat(SubCarrInd(:),1,M) - PhsCons*ones(N,M), 'fro' ) )
%             cvx_end
%             PhsSlope
%             PhsCons
            
else
    %% performing the same using cvxgen
    PhsRelFirstPac = unwrap(angle(vna_response));
    for antIdForPhs = 1:M
        if  PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) > pi
            PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) - 2*pi;
        elseif PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) < -pi
            PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) + 2*pi;
        end
    end
    % figure(201); plot(unwrap(angle(vna_response))); 
    params = struct;
    params.PhsRelFirstPacVec = PhsRelFirstPac(:);
    paramSlopeVecTmp = repmat(SubCarrInd(:),1,M);
    params.paramSlopeVec = paramSlopeVecTmp(:);
    params.paramConsVec = ones(N*M,1);
    settings = struct;
    settings.verbose = 0;
    [vars, status] = csolve(params, settings);
    PhsSlope = vars.PhsSlope;
    PhsCons = vars.PhsCons;
    
    ToMult = exp(1i* (-PhsSlope*repmat(SubCarrInd(:),1,M) - PhsCons*ones(N,M) ));
%     vna_response_corrected = vna_response.*ToMult;          

end