function [PhsSlope, PhsCons] = removePhsSlope(vna_response,M,SubCarrInd,N)%#codegen
useCvxgen = 0;
if ~useCvxgen
    PhsRelFirstPac = unwrap(angle(vna_response));
    % angle��ȡ��λ��,��������vna_response ��ÿ��Ԫ�ط�����λ�ǣ��Ի���Ϊ��λ�����˽ǶȽ��� ���� ֮�䡣
    % unwrap ����ƣ�ʹ��λ��pi�����������䣬�Ӷ���Ӧ����ʵ����λ�仯,ͨ�������� P ������ ��2�� �ı���������������λ��
    % % Below code is for when you are using phase relative to
    % % the first packet.
    for antIdForPhs = 1:M
        if  PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) > pi
            PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) - 2*pi;
            % �����������������Ԫ�ض������������Ĵ���
        elseif PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) < -pi
            PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) + 2*pi;
        end
    end
    A = [repmat(SubCarrInd(:), M, 1) ones(N*M, 1)];
    x = A\PhsRelFirstPac(:);
    %���൱��inv��A��*B����˼����A���B,�൱��A����������B��
    %x = A\B �Ƿ��� Ax = B �Ľ⡣���� A �� B ����ӵ����ͬ��������
    %PhsRelFirstPac(:)
    %������չ��Ϊ90*1��1234-1324
    PhsSlope = x(1);
    PhsCons = x(2);%xΪ2�׾���
    
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