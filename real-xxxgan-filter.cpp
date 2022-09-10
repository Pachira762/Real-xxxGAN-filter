#include "pch.h"
#include "real-xxxgan-filter.h"
#include <filesystem>

RealXxxGanFilter::RealXxxGanFilter() {
	ncnn::create_gpu_instance();

	gpu_id_ = ncnn::get_default_gpu_index();
}

RealXxxGanFilter::~RealXxxGanFilter() {
	realcugan_ = nullptr;
	realesrgan_ = nullptr;

	ncnn::destroy_gpu_instance();
}

bool RealXxxGanFilter::SetSize(int w, int h, int scale) {
	AllocBuffer(w, h, input_);
	AllocBuffer(scale * w, scale * h, output_);

	return true;
}

bool RealXxxGanFilter::Process(Mode mode, int scale, int denoise, bool tta) {
	if (scale == 1) {
		memcpy(output_.data, input_.data, 4 * input_.w * input_.h);
		return true;
	}

	if ((!realcugan_ && !realesrgan_) || mode_ != mode || scale_ != scale || denoise_ != denoise || tta_ != tta) {
		if (!Configurate(mode, scale, denoise, tta)) {
			return false;
		}
	}

	if (mode == Mode::RealCUGAN) {
		if (!realcugan_ || realcugan_->process(input_, output_) != 0) {
			return false;
		}
	}
	else {
		if (!realesrgan_ || realesrgan_->process(input_, output_) != 0) {
			return false;
		}
	}

	return true;
}

std::wstring RealXxxGanFilter::GetModelFolder(Mode mode) {
	switch (mode) {
	case Mode::RealCUGAN: return L"plugins\\models\\models-se\\";
	default: return L"plugins\\models\\";
	}
}

std::wstring RealXxxGanFilter::GetModelName(Mode mode, int scale, int denoise) {
	std::wstring name{};

	if (mode == Mode::RealCUGAN) {
		name += L"up" + std::to_wstring(scale) + L"x";

		if (scale >= 3 && denoise >= 1) {
			denoise = 3;
		}

		switch (denoise) {
		case -1:
			name += L"-conservative";
			break;

		case 0:
			name += L"-no-denoise";
			break;

		default:
			name += L"-denoise" + std::to_wstring(denoise) + L"x";
			break;
		}

	}
	else if (mode == Mode::RealESRGAN_AnimeVideoV3) {
		name += L"realesr-animevideov3-x" + std::to_wstring(scale);
	}
	else if (mode == Mode::RealESRGAN_X4Plus) {
		name += L"realesrgan-x4plus";
	}
	else if (mode == Mode::RealESRGAN_X4PlusAnime) {
		name += L"realesrgan-x4plus-anime";
	}

	return name;
}

int RealXxxGanFilter::GetPrepadding(Mode mode, int scale) {
	if (mode == Mode::RealCUGAN) {
		switch (scale) {
		case 2: return 18;
		case 3: return 14;
		case 4: return 19;
		default: return 0;
		}
	}
	else {
		return 10;
	}
}

int RealXxxGanFilter::GetTileSize(Mode mode, int scale) {
	uint32_t heap_budget = ncnn::get_gpu_device(gpu_id_)->get_heap_budget();

	if (mode == Mode::RealCUGAN) {
		switch (scale) {
		case 2:
			if (heap_budget > 1300)
				return 400;
			else if (heap_budget > 800)
				return 300;
			else if (heap_budget > 400)
				return 200;
			else if (heap_budget > 200)
				return 100;
			else
				return 32;

		case 3:
			if (heap_budget > 3300)
				return 400;
			else if (heap_budget > 1900)
				return 300;
			else if (heap_budget > 950)
				return 200;
			else if (heap_budget > 320)
				return 100;
			else
				return 32;

		case 4:
			if (heap_budget > 1690)
				return 400;
			else if (heap_budget > 980)
				return 300;
			else if (heap_budget > 530)
				return 200;
			else if (heap_budget > 240)
				return 100;
			else
				return 32;

		default:
			return 32;
		}
	}
	else {
		if (heap_budget > 1900)
			return 200;
		else if (heap_budget > 550)
			return 100;
		else if (heap_budget > 190)
			return 64;
		else
			return 32;
	}

}

bool RealXxxGanFilter::Configurate(Mode mode, int scale, int denoise, bool tta) {
	realcugan_ = nullptr;
	realesrgan_ = nullptr;

	std::wstring folder = GetModelFolder(mode);
	std::wstring name = GetModelName(mode, scale, denoise);
	auto param_path = folder + name + L".param";
	auto model_path = folder + name + L".bin";

	if (!std::filesystem::exists(param_path) || !std::filesystem::exists(model_path)) {
		auto msg = std::wstring(L"Failed to find model file\r\n") + param_path + L"\r\n" + model_path;
		MessageBoxW(NULL, msg.c_str(), L"Real-xxxGAN", MB_OK);
		return false;
	}

	if (mode == Mode::RealCUGAN) {
		auto realcugan = std::make_unique<RealCUGAN>(gpu_id_, tta);
		if (realcugan->load(param_path, model_path) != 0) {
			return false;
		}

		realcugan->noise = denoise;
		realcugan->scale = scale;
		realcugan->tilesize = GetTileSize(mode, scale);
		realcugan->prepadding = GetPrepadding(mode, scale);
		realcugan->syncgap = 1;

		realcugan_ = std::move(realcugan);
	}
	else {
		auto realesrgan = std::make_unique<RealESRGAN>(gpu_id_, tta);
		if (realesrgan->load(param_path, model_path) != 0) {
			return false;
		}

		realesrgan->scale = scale;
		realesrgan->tilesize = GetTileSize(mode, scale);
		realesrgan->prepadding = GetPrepadding(mode, scale);

		realesrgan_ = std::move(realesrgan);
	}

	mode_ = mode;
	scale_ = scale;
	denoise_ = denoise;
	tta_ = tta;

	return true;
}

void RealXxxGanFilter::AllocBuffer(int w, int h, ncnn::Mat& mat) {
	if (mat.data == nullptr || mat.w != w || mat.h != h) {
		mat = ncnn::Mat(w, h, (size_t)4, 4);
	}
}
