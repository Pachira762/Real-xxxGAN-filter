#pragma once
#include <memory>
#include "filter.h"
#include "realcugan.h"
#include "realesrgan.h"

enum class Mode {
	RealCUGAN,
	RealESRGAN_AnimeVideoV3,
	RealESRGAN_X4Plus,
	RealESRGAN_X4PlusAnime,
};

class RealXxxGanFilter {
public:
	RealXxxGanFilter();
	~RealXxxGanFilter();

	bool SetSize(int w, int h, int scale);
	bool Process(Mode mode, int scale, int denoise, bool tta);

private:
	int gpu_id_ = -1;

	Mode mode_ = Mode::RealCUGAN;
	int scale_ = 2;
	int denoise_ = -1;
	bool tta_ = false;

	std::unique_ptr<RealCUGAN> realcugan_ = nullptr;
	std::unique_ptr<RealESRGAN> realesrgan_ = nullptr;

	ncnn::Mat input_{};
	ncnn::Mat output_{};

	bool Configurate(Mode mode, int scale, int denoise, bool tta);
	void AllocBuffer(int w, int h, ncnn::Mat& mat);

	std::wstring GetModelFolder(Mode mode);
	std::wstring GetModelName(Mode mode, int scale, int denoise);
	int GetPrepadding(Mode mode, int scale);
	int GetTileSize(Mode mode, int scale);

public:
	BYTE* GetInputBuffer() {
		return (BYTE*)input_.data;
	}

	BYTE* GetOutputBuffer() {
		return (BYTE*)output_.data;
	}
};
